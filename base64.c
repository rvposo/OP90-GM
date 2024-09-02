#include <stdint.h>
#include <stdlib.h>
#include "CyberXML.h"
#include "b64.h"
/*
Base64 é um método para codificação de dados para transferência na Internet (codificação MIME para transferência de conteúdo). 
É utilizado frequentemente para transmitir dados binários por meios de transmissão que lidam apenas com texto, como por exemplo 
para enviar arquivos anexos por e-mail.

É constituído por 64 caracteres ([A-Z],[a-z],[0-9], "/" e "+") que deram origem ao seu nome. 
O carácter "=" é utilizado como um sufixo especial e a especificação original (RFC 989) definiu que o símbolo "*" 
pode ser utilizado para delimitar dados convertidos, mas não criptografados, dentro de um stream.

Exemplo de codificação:

Texto original: hello world
Texto convertido para base64: aGVsbG8gd29ybGQ=
A codificação base64 é frequentemente utilizada quando existe uma necessidade de transferência e armazenamento 
de dados binários para um dispositivo designado para trabalhar com dados textuais. 
Esta codificação é amplamente utilizada por aplicações em conjunto com a linguagem de marcação XML, possibilitando 
o armazenamento de dados binários em forma de texto.


Texto							M	a	n
ASCII			77 (0x4d)	97 (0x61)	110 (0x6e)
Binário	0	1	0	0	1	1	0	1	0	1	1	0	0	0	0	1	0	1	1	0	1	1	1	0
Valor correspondente (index)	19	22	5	46
Codificado em base64			T	W	F	u
Como ilustrado neste exemplo, três octetos são representados em base64 como quatro caracteres.

A tabela de equivalência entre valores correspondentes (index) e os caracteres utilizados para codificação:

Valor	Caractere	 	Valor	Caractere	 	Valor	Caractere	 	Valor	Caractere
0			A			16			Q			32			g			48			w
1			B			17			R			33			h			49			x
2			C			18			S			34			i			50			y
3			D			19			T			35			j			51			z
4			E			20			U			36			k			52			0
5			F			21			V			37			l			53			1
6			G			22			W			38			m			54			2
7			H			23			X			39			n			55			3
8			I			24			Y			40			o			56			4
9			J			25			Z			41			p			57			5
10			K			26			a			42			q			58			6
11			L			27			b			43			r			59			7
12			M			28			c			44			s			60			8
13			N			29			d			45			t			61			9
14			O			30			e			46			u			62			+
15			P			31			f			47			v			63			/
Quando o número de bytes a ser convertido não for divisível por três 
(se houver somente um ou dois bytes para compor o último bloco de 24 bits), o seguinte algoritmo é aplicado:
Adiciona-se o número necessário de bytes com valor zero para que haja 3 bytes. 
Assim, o bloco fica completo e a conversão é feita normalmente.
Se houver somente um byte de entrada significativo, somente os dois primeiros dígitos codificados 
em base64 (12 bits) são mantidos, e se houverem dois bytes, os três primeiros dígitos codificados 
(18 bits) são mantidos. O caractere '=' pode ser adicionado para que o último bloco codificado possua 4 caracteres. 
Assim, quando o último grupo contiver um octeto, os 4 bits menos significativos do grupo final de 6 bits são zero; 
e quando o último grupo contiver dois octetos, os dois bits menos significativos do grupo de 6 bits são zero.

*/
#ifdef b64_USE_CUSTOM_MALLOC
extern void* b64_malloc(size_t);
#endif

#ifdef b64_USE_CUSTOM_REALLOC
extern void* b64_realloc(void*, size_t);
#endif

void build_decoding_table(void);

char *base64_encode(const unsigned char *data,size_t input_length, size_t *output_length)
{
int i = 0, j;
char *encoded_data;

    *output_length = 4 * ((input_length + 2) / 3);

    encoded_data = malloc(*output_length+1);
    if (encoded_data == NULL) return NULL;

    for (i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = b64_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = b64_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = b64_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = b64_table[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';
	encoded_data[*output_length] = '\0';
    return encoded_data;
}

unsigned char *base64_decode(const char *data, size_t input_length,size_t *output_length)
{
unsigned char *decoded_data;
int i, j;

    if (decoding_table == NULL) build_decoding_table();

    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    decoded_data = malloc(*output_length+1);
    if (decoded_data == NULL) return NULL;

    for (i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
	decoded_data[*output_length] = '\0';
    return decoded_data;
}

void build_decoding_table(void) {
int i;

    decoding_table = malloc(256);

    for (i = 0; i < 64; i++)
        decoding_table[(unsigned char) b64_table[i]] = i;
}

void base64_cleanup() {
    free(decoding_table);
}
/*------------------------------------------------------------------------------*/
char * b64_encode (const unsigned char *src, size_t len)
{
  int i = 0;
  int j = 0;
  char *enc = NULL;
  size_t size = 0;
  unsigned char buf[4];
  unsigned char tmp[3]={0};

  // alloc
  enc = (char *) b64_malloc(1);
  if (NULL == enc) { return NULL; }

  // parse until end of source
  while (len--) {
    // read up to 3 bytes at a time into `tmp'
    tmp[i++] = *(src++);

    // if 3 bytes read then encode into `buf'
    if (3 == i) {
      buf[0] = (tmp[0] & 0xfc) >> 2;
      buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
      buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
      buf[3] = tmp[2] & 0x3f;

      // allocate 4 new byts for `enc` and
      // then translate each encoded buffer
      // part by index from the base 64 index table
      // into `enc' unsigned char array
      enc = (char *) b64_realloc(enc, size + 4);
      for (i = 0; i < 4; ++i) {
        enc[size++] = b64_table[buf[i]];
      }

      // reset index
      i = 0;
    }
  }

  // remainder
  if (i > 0) {
    // fill `tmp' with `\0' at most 3 times
    for (j = i; j < 3; ++j) {
      tmp[j] = '\0';
    }

    // perform same codec as above
    buf[0] = (tmp[0] & 0xfc) >> 2;
    buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
    buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
    buf[3] = tmp[2] & 0x3f;

    // perform same write to `enc` with new allocation
    for (j = 0; (j < i + 1); ++j) {
      enc = (char *) b64_realloc(enc, size + 1);
      enc[size++] = b64_table[buf[j]];
    }

    // while there is still a remainder
    // append `=' to `enc'
    while ((i++ < 3)) {
      enc = (char *) b64_realloc(enc, size + 1);
      enc[size++] = '=';
    }
  }

  // Make sure we have enough space to add '\0' character at end.
  enc = (char *) b64_realloc(enc, size + 1);
  enc[size] = '\0';

  return enc;
}
				  
unsigned char *
b64_decode (const char *src, size_t len) {
  return b64_decode_ex(src, len, NULL);
}

unsigned char *
b64_decode_ex (const char *src, size_t len, size_t *decsize) {
  int i = 0;
  int j = 0;
  int l = 0;
  size_t size = 0;
  unsigned char *dec = NULL;
  unsigned char buf[3]={0};
  unsigned char tmp[4]={0};

  // alloc
  dec = (unsigned char *) b64_malloc(1);
  if (NULL == dec) { return NULL; }

  // parse until end of source
  while (len--) {
    // break if char is `=' or not base64 char
    if ('=' == src[j]) { break; }
    if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) { break; }

    // read up to 4 bytes at a time into `tmp'
    tmp[i++] = src[j++];

    // if 4 bytes read then decode into `buf'
    if (4 == i) {
      // translate values in `tmp' from table
      for (i = 0; i < 4; ++i) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[i] == b64_table[l]) {
            tmp[i] = l;
            break;
          }
        }
      }

      // decode
      buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
      buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
      buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

      // write decoded buffer to `dec'
      dec = (unsigned char *) b64_realloc(dec, size + 3);
      if (dec != NULL){
        for (i = 0; i < 3; ++i) {
          dec[size++] = buf[i];
        }
      } else {
        return NULL;
      }

      // reset
      i = 0;
    }
  }

  // remainder
  if (i > 0) {
    // fill `tmp' with `\0' at most 4 times
    for (j = i; j < 4; ++j) {
      tmp[j] = '\0';
    }

    // translate remainder
    for (j = 0; j < 4; ++j) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[j] == b64_table[l]) {
            tmp[j] = l;
            break;
          }
        }
    }

    // decode remainder
    buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
    buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
    buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

    // write remainer decoded buffer to `dec'
    dec = (unsigned char *) b64_realloc(dec, size + (i - 1));
    if (dec != NULL){
      for (j = 0; (j < i - 1); ++j) {
        dec[size++] = buf[j];
      }
    } else {
      return NULL;
    }
  }

  // Make sure we have enough space to add '\0' character at end.
  dec = (unsigned char *) b64_realloc(dec, size + 1);
  if (dec != NULL){
    dec[size] = '\0';
  } else {
    return NULL;
  }

  // Return back the size of decoded string if demanded.
  if (decsize != NULL) {
    *decsize = size;
  }

  return dec;
}

