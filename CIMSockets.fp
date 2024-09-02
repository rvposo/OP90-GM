s��        ��   / �  �   �   ����                               CIMSockets                                                                                                                               � ��const char *     � ��LCID     	� 	��ERRORINFO  �  � ��HRESULT  � � ��SAFEARRAY *  � 	� 	��LPUNKNOWN     � ��VARIANT  � � ��VBOOL  �  � ��SCODE  � � ��CAObjHandle  � � ��DATE     � ��CURRENCY  `    Use this function to create a new _SMF object, and obtain a handle to the object.

If the server application is already running, this function may or may not start another copy of the application.  This is determined by the server application.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.        The name or IP address of the machine on which you want to run the ActiveX server.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL for this parameter, and there is a RemoteServerName registry entry for this server, the server will be run on the machine specified by the RemoteServerName entry.

If you pass NULL for this parameter and there is no RemoteServerName registry entry for this server, the server will be run on the same machine as your program.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.     
����  �    Status                            . -   �  �    Server                            8 - �     �    Support Multithreading            � -� �  �    Locale                            
O �      �    Reserved                          
� � � �  �    Object Handle                      	           NULL    1    LOCALE_NEUTRAL    0    	          p    Use this function to load an existing _SMF object from a file, and obtain a handle to the object.

If the server application is already running, this function may or may not start another copy of the application.  This is determined by the server application.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.     :    A file containing the data for an ActiveX server object.        The name or IP address of the machine on which you want to run the ActiveX server.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL for this parameter, and there is an ActivateAtStorage registry entry for this server, the server will be run on the machine on which the file specified by the filename parameter resides.

If you pass NULL for this parameter and there is no ActivateAtStorage registry entry for this server, the server will be run on the same machine as your program.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.    d
����  �    Status                            r -   �  �    File Name                         � - � �  �    Server                            � -�     �    Support Multithreading            � �  �  �    Locale                            � � �     �    Reserved                          8 �� �  �    Object Handle                      	               NULL    1    LOCALE_NEUTRAL    0    	          �    Use this function to get a handle to an active _SMF object.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.    �    The name or IP address of the machine on which to look for the active ActiveX server object.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL, the function will look for the active ActiveX server object on the same machine as your program.

NOTE: Windows 95 and Windows NT 4.0 do not support accessing active objects on remote machines.  Future versions of these operating systems may support this functionality.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.    t
����  �    Status                            � -   �  �    Server                            ` - �     �    Support Multithreading             -� �  �    Locale                             w �      �    Reserved                           � � � �  �    Object Handle                      	           NULL    1    LOCALE_NEUTRAL    0    	              A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    #
����  �    Status                            %3 -   �  �    Object Handle                     &x - � �  �    Error Info                        (� -�    �    My_sock ID                         	                       NULL    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    *

����  �    Status                            ,) -   �  �    Object Handle                     -n - � �  �    Error Info                        /� -�    �    My_sock ID                         	                       NULL           A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    0�
����  �    Status                            3 -   �  �    Object Handle                     4\ - � �  �    Error Info                        6� -�    �    My_Base Timestamp                  	                       NULL    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    7�
����  �    Status                            : -   �  �    Object Handle                     ;R - � �  �    Error Info                        =~ -�    �    My_Base Timestamp                  	                       NULL           A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     �    Documentation for this function, if provided by the server, is located in the function help.

When it is no longer needed, you must the string returned in this parameter by calling the CVI ActiveX Library function CA_FreeMemory.    >�
����  �    Status                            @� -   �  �    Object Handle                     B@ - � �  �    Error Info                        Dl -�    �    My_Base Data                       	                       NULL    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    FZ
����  �    Status                            Hy -   �  �    Object Handle                     I� - � �  �    Error Info                        K� -� �  �    My_Base Data                       	                       NULL    ""       A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     �    Documentation for this function, if provided by the server, is located in the function help.

When it is no longer needed, you must the string returned in this parameter by calling the CVI ActiveX Library function CA_FreeMemory.    MJ
����  �    Status                            Oi -   �  �    Object Handle                     P� - � �  �    Error Info                        R� -�    �    My_Station_ID                      	                       NULL    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    T�
����  �    Status                            V� -   �  �    Object Handle                     X, - � �  �    Error Info                        ZX -� �  �    My_Station_ID                      	                       NULL    ""       A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    [�
����  �    Status                            ]� -   �  �    Object Handle                     _ - � �  �    Error Info                        aH -�    �    My_Timeout                         	                       NULL    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    b�
����  �    Status                            d� -   �  �    Object Handle                     f - � �  �    Error Info                        h> -�    �    My_Timeout                         	                       NULL           A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     �    Documentation for this function, if provided by the server, is located in the function help.

When it is no longer needed, you must the string returned in this parameter by calling the CVI ActiveX Library function CA_FreeMemory.    i�
����  �    Status                            k� -   �  �    Object Handle                     m  - � �  �    Error Info                        o, -� �  �    Arquivo                           o� �  �  �    Secao                             o� � � �  �    Linha                             p^ ��    �    Arg4                               	                       NULL    ""    ""    ""    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    r�
����  �    Status                            u -   �  �    Object Handle                     va - � �  �    Error Info                        x� -� �  �    Arquivo                           x� �  �  �    Secao                             yY � � �  �    Linha                             y� �� �  �    Parametro                         z% �     �    Arg5                               	                       NULL    ""    ""    ""    ""    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    |w
����  �    Status                            ~� -   �  �    Object Handle                     � - � �  �    Error Info                        � -� �  �    Host                              �m �  �  �    Service                           �� � �    �    Timeout                           �9 ��    �    Arg4                               	                       NULL    ""    ""        	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    �N
����  �    Status                            �m -   �  �    Object Handle                     �� - � �  �    Error Info                        �� -�    �    Sock ID                           �D �  �  �    Station                           �� � �    �    Timeout                           � ��    �    Arg4                               	                       NULL        ""        	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    �#
����  �    Status                            �B -   �  �    Object Handle                     �� - � �  �    Error Info                        �� -�    �    Sock ID                           � �     �    Timeout                           � � �    �    Arg3                               	                       NULL            	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     �    Documentation for this function, if provided by the server, is located in the function help.

When it is no longer needed, you must the string returned in this parameter by calling the CVI ActiveX Library function CA_FreeMemory.    �W
����  �    Status                            �v -   �  �    Object Handle                     �� - � �  �    Error Info                        �� -�    �    Result                            �M �     �    Arg2                               	                       NULL        	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    �t
����  �    Status                            �� -   �  �    Object Handle                     �� - � �  �    Error Info                        � -�    �    Sock ID                           �j �     �    Timeout                           �� � � �  �    Station                           �6 �� �  �    Barcode                           �� �  �  �    Status                            � � �    �    Arg6                               	                       NULL            ""    ""    ""    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    ^    Documentation for this function, if provided by the server, is located in the function help.

The string passed in this parameter must be allocated by calling the CVI ActiveX Library function CA_AllocMemory.

When it is no longer needed, the string returned in this parameter must be freed by calling the CVI ActiveX Library function CA_FreeMemory.     ^    Documentation for this function, if provided by the server, is located in the function help.    ��
����  �    Status                            �� -   �  �    Object Handle                     �� - � �  �    Error Info                        � -�    �    Sock ID                           �� �     �    Timeout                           �� � � �  �    Station                           �M �� �  �    Barcode                           �� �     �    Mensagem_retorno                  � � �    �    Arg6                               	                       NULL            ""    ""    	            	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    m    Documentation for this function, if provided by the server, is located in the function help.

The Array Functions class in the CVI ActiveX Library contains functions to help convert a Safe Array into a C Style array. If you do not convert the Safe Array into a C Style array, you must free the Safe Array using the CVI ActiveX Library function CA_SafeArrayDestroy     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    ��
����  �    Status                            ��    �  �    Object Handle                     �  � �  �    Error Info                        �8 �    �    Sock ID                           �� i     �    Timeout                           � i � �  �    Station                           �j i� �  �    Box Barcode                       �� �  �  �    Barcode                           �E � �    �    Quantidade                        �� ��    �    Arg7                               	                       NULL            ""    ""    	               	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    �s
����  �    Status                            ��  	  �  �    Object Handle                     ��  � �  �    Error Info                        �     �    Sock ID                           �i �    �    Timeout                           �� i 	 �  �    Station                           �5 i � �  �    Unit Id                           ƛ i �  �    Group Id                          � i� �  �    Group Version                     �g � 	 �  �    Test Id                           �� � � 	�  �    Test Result                       �3 � 
   �    Test Value                        ș ��    �    Flag                              �� � 	    �    Arg11                              	                       NULL            ""    ""    ""    ""    ""    ""            	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     �    Documentation for this function, if provided by the server, is located in the function help.

When it is no longer needed, you must the string returned in this parameter by calling the CVI ActiveX Library function CA_FreeMemory.    ̫
����  �    Status                            �� -   �  �    Object Handle                     � - � �  �    Error Info                        �; -�    �    Arg1                               	                       NULL    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    �)
����  �    Status                            �H -   �  �    Object Handle                     ׍ - � �  �    Error Info                        ٹ -�    �    Sock ID                           � �     �    Timeout                           څ � � �  �    Station                           �� �� �  �    Barcode Pai                       �Q �  �  �    Barcode Filho                     ۷ � �    �    Arg6                               	                       NULL            ""    ""    ""    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    ^    Documentation for this function, if provided by the server, is located in the function help.

The string passed in this parameter must be allocated by calling the CVI ActiveX Library function CA_AllocMemory.

When it is no longer needed, the string returned in this parameter must be freed by calling the CVI ActiveX Library function CA_FreeMemory.     ^    Documentation for this function, if provided by the server, is located in the function help.    �@
����  �    Status                            �_    �  �    Object Handle                     �  � �  �    Error Info                        �� �    �    Sock ID                           �6 i     �    Timeout                           � i � �  �    Station                           � i� �  �    Operator_id                       �h �  �  �    Onoff                             �� � �    �    Mensagem_retorno                  �4 ��    �    Arg7                               	                       NULL            ""    ""    ""    	            	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    =    An ActiveX object handle obtained from New_SMF, Open_SMF, Active_SMF, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    m    Documentation for this function, if provided by the server, is located in the function help.

The Array Functions class in the CVI ActiveX Library contains functions to help convert a Safe Array into a C Style array. If you do not convert the Safe Array into a C Style array, you must free the Safe Array using the CVI ActiveX Library function CA_SafeArrayDestroy    m    Documentation for this function, if provided by the server, is located in the function help.

The Array Functions class in the CVI ActiveX Library contains functions to help convert a Safe Array into a C Style array. If you do not convert the Safe Array into a C Style array, you must free the Safe Array using the CVI ActiveX Library function CA_SafeArrayDestroy    m    Documentation for this function, if provided by the server, is located in the function help.

The Array Functions class in the CVI ActiveX Library contains functions to help convert a Safe Array into a C Style array. If you do not convert the Safe Array into a C Style array, you must free the Safe Array using the CVI ActiveX Library function CA_SafeArrayDestroy    m    Documentation for this function, if provided by the server, is located in the function help.

The Array Functions class in the CVI ActiveX Library contains functions to help convert a Safe Array into a C Style array. If you do not convert the Safe Array into a C Style array, you must free the Safe Array using the CVI ActiveX Library function CA_SafeArrayDestroy    m    Documentation for this function, if provided by the server, is located in the function help.

The Array Functions class in the CVI ActiveX Library contains functions to help convert a Safe Array into a C Style array. If you do not convert the Safe Array into a C Style array, you must free the Safe Array using the CVI ActiveX Library function CA_SafeArrayDestroy     ^    Documentation for this function, if provided by the server, is located in the function help.    ��
����  �    Status                            �  	  �  �    Object Handle                     �b  � �  �    Error Info                        �     �    Sock ID                           �� �    �    Timeout                           �Z i 	 �  �    Station                           �� i � �  �    Group Id                          �& i �  �    Group Version                     � i�    �    Quantidade                        �� � 	 �  �    Test Id                           �g � � 	�  �    Test Desc                         �� � 
�  �    Low Limit                         �Q �� �  �    High Limit                        �� � 	 �  �    Un Med                            �; � �    �    Arg12                              	                       NULL            ""    ""    ""        	           	           	           	           	           	           a    Use this function to create a new _Comm object, and obtain a handle to the object.

If the server application is already running, this function may or may not start another copy of the application.  This is determined by the server application.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.        The name or IP address of the machine on which you want to run the ActiveX server.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL for this parameter, and there is a RemoteServerName registry entry for this server, the server will be run on the machine specified by the RemoteServerName entry.

If you pass NULL for this parameter and there is no RemoteServerName registry entry for this server, the server will be run on the same machine as your program.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.    ��
����  �    Status                            � -   �  �    Server                           � - �     �    Support Multithreading            -� �  �    Locale                           � �      �    Reserved                         $ � � �  �    Object Handle                      	           NULL    1    LOCALE_NEUTRAL    0    	          q    Use this function to load an existing _Comm object from a file, and obtain a handle to the object.

If the server application is already running, this function may or may not start another copy of the application.  This is determined by the server application.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.     :    A file containing the data for an ActiveX server object.        The name or IP address of the machine on which you want to run the ActiveX server.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL for this parameter, and there is an ActivateAtStorage registry entry for this server, the server will be run on the machine on which the file specified by the filename parameter resides.

If you pass NULL for this parameter and there is no ActivateAtStorage registry entry for this server, the server will be run on the same machine as your program.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.   
�
����  �    Status                           � -   �  �    File Name                        @ - � �  �    Server                           c -�     �    Support Multithreading            �  �  �    Locale                           z � �     �    Reserved                         � �� �  �    Object Handle                      	               NULL    1    LOCALE_NEUTRAL    0    	          �    Use this function to get a handle to an active _Comm object.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.    �    The name or IP address of the machine on which to look for the active ActiveX server object.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL, the function will look for the active ActiveX server object on the same machine as your program.

NOTE: Windows 95 and Windows NT 4.0 do not support accessing active objects on remote machines.  Future versions of these operating systems may support this functionality.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.   
����  �    Status                            -   �  �    Server                           � - �     �    Support Multithreading           � -� �  �    Locale                            �      �    Reserved                         N � � �  �    Object Handle                      	           NULL    1    LOCALE_NEUTRAL    0    	              A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    @    An ActiveX object handle obtained from New_Comm, Open_Comm, Active_Comm, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.   �
����  �    Status                            � -   �  �    Object Handle                    " - � �  �    Error Info                       $4 -�    �    Com Port                         $� �  �  �    Com Settings                     %  � �    �    Arg3                               	                       NULL        ""    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    @    An ActiveX object handle obtained from New_Comm, Open_Comm, Active_Comm, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.   &�
����  �    Status                           (� -   �  �    Object Handle                    *A - � �  �    Error Info                       ,m -�    �    Arg1                               	                       NULL    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    @    An ActiveX object handle obtained from New_Comm, Open_Comm, Active_Comm, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.    ^    Documentation for this function, if provided by the server, is located in the function help.

The string passed in this parameter must be allocated by calling the CVI ActiveX Library function CA_AllocMemory.

When it is no longer needed, the string returned in this parameter must be freed by calling the CVI ActiveX Library function CA_FreeMemory.     ^    Documentation for this function, if provided by the server, is located in the function help.   -�
����  �    Status                           /� -   �  �    Object Handle                    1: - � �  �    Error Info                       3f -�    �    Buffer                           4� �     �    Arg2                               	                       NULL    	            	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    @    An ActiveX object handle obtained from New_Comm, Open_Comm, Active_Comm, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.   6s
����  �    Status                           8� -   �  �    Object Handle                    9� - � �  �    Error Info                       < -� �  �    Buffer                           <l �     �    Arg2                               	                       NULL    ""    	           h    Use this function to create a new _TRANSPONDER object, and obtain a handle to the object.

If the server application is already running, this function may or may not start another copy of the application.  This is determined by the server application.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.        The name or IP address of the machine on which you want to run the ActiveX server.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL for this parameter, and there is a RemoteServerName registry entry for this server, the server will be run on the machine specified by the RemoteServerName entry.

If you pass NULL for this parameter and there is no RemoteServerName registry entry for this server, the server will be run on the same machine as your program.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.   @}
����  �    Status                           A� -   �  �    Server                           C� - �     �    Support Multithreading           EQ -� �  �    Locale                           F� �      �    Reserved                         F� � � �  �    Object Handle                      	           NULL    1    LOCALE_NEUTRAL    0    	          x    Use this function to load an existing _TRANSPONDER object from a file, and obtain a handle to the object.

If the server application is already running, this function may or may not start another copy of the application.  This is determined by the server application.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.     :    A file containing the data for an ActiveX server object.        The name or IP address of the machine on which you want to run the ActiveX server.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL for this parameter, and there is an ActivateAtStorage registry entry for this server, the server will be run on the machine on which the file specified by the filename parameter resides.

If you pass NULL for this parameter and there is no ActivateAtStorage registry entry for this server, the server will be run on the same machine as your program.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.   K�
����  �    Status                           L� -   �  �    File Name                        M - � �  �    Server                           O< -�     �    Support Multithreading           P� �  �  �    Locale                           RS � �     �    Reserved                         R� �� �  �    Object Handle                      	               NULL    1    LOCALE_NEUTRAL    0    	          �    Use this function to get a handle to an active _TRANSPONDER object.

You must call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED if you register any ActiveX event callbacks and want the callbacks to be called from the same thread in which they were registered.  If you do not call CA_InitActiveXThreadStyleForCurrentThread with COINIT_APARTMENTTHREADED your callbacks will be called from a system thread.        A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code.    �    The name or IP address of the machine on which to look for the active ActiveX server object.  The name can be either a UNC name ("\\playdough")  or DNS name ("plato.natinst.com").

If you pass NULL, the function will look for the active ActiveX server object on the same machine as your program.

NOTE: Windows 95 and Windows NT 4.0 do not support accessing active objects on remote machines.  Future versions of these operating systems may support this functionality.    �    Pass 0 if you use the object only from the thread that calls this function.  Pass 1 if you use the object from multiple threads.

The CVI ActiveX library uses the COM Global Interface Table (GIT) to marshal interface pointers between threads.  There is overhead associated with using the GIT that should be avoided when possible.  If you do not pass the CAObjHandle between threads in your application, you do not need to use the GIT.    S    Pass the locale for the object.  This value tells the object how to interpret arguments to its methods.  Pass LOCALE_NEUTRAL to indicate the default language-neutral locale.  This value is not used by the server when you call it through a dual interface method.

The CVI ActiveX library passes this value to the IDispatch::Invoke method.     B    This parameter is reserved.  You must pass 0 for this parameter.     �    A handle to the requested ActiveX object.

Use this handle to call methods and get/set properties of this ActiveX object.

When it is no longer needed, you must discard this handle using CA_DiscardObjHandle.   V�
����  �    Status                           W� -   �  �    Server                           Y� - �     �    Support Multithreading           [� -� �  �    Locale                           \� �      �    Reserved                         ]. � � �  �    Object Handle                      	           NULL    1    LOCALE_NEUTRAL    0    	              A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    U    An ActiveX object handle obtained from New_TRANSPONDER, Open_TRANSPONDER, Active_TRANSPONDER, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    ^    Documentation for this function, if provided by the server, is located in the function help.

The string passed in this parameter must be allocated by calling the CVI ActiveX Library function CA_AllocMemory.

When it is no longer needed, the string returned in this parameter must be freed by calling the CVI ActiveX Library function CA_FreeMemory.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.   _�
����  �    Status                           a� -   �  �    Object Handle                    b� - � �  �    Error Info                       e) -�    �    Com Port                         e� �     �    Buffer                           f� � �    �    Timeout                          g[ ��    �    Arg4                               	                       NULL        	                	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    U    An ActiveX object handle obtained from New_TRANSPONDER, Open_TRANSPONDER, Active_TRANSPONDER, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    ^    Documentation for this function, if provided by the server, is located in the function help.

The string passed in this parameter must be allocated by calling the CVI ActiveX Library function CA_AllocMemory.

When it is no longer needed, the string returned in this parameter must be freed by calling the CVI ActiveX Library function CA_FreeMemory.     ^    Documentation for this function, if provided by the server, is located in the function help.   it
����  �    Status                           k� -   �  �    Object Handle                    l� - � �  �    Error Info                       o -� �  �    Var_transponder                  o� �  �  �    Modelo                           o� � �    �    Numserie                         qN ��    �    Arg4                               	                       NULL    ""    ""    	            	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    U    An ActiveX object handle obtained from New_TRANSPONDER, Open_TRANSPONDER, Active_TRANSPONDER, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.    ^    Documentation for this function, if provided by the server, is located in the function help.

The string passed in this parameter must be allocated by calling the CVI ActiveX Library function CA_AllocMemory.

When it is no longer needed, the string returned in this parameter must be freed by calling the CVI ActiveX Library function CA_FreeMemory.     ^    Documentation for this function, if provided by the server, is located in the function help.   sk
����  �    Status                           u� -   �  �    Object Handle                    v� - � �  �    Error Info                       y -� �  �    Var_transponder                  yy �     �    Numserie                         z� � �    �    Arg3                               	                       NULL    ""    	            	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    U    An ActiveX object handle obtained from New_TRANSPONDER, Open_TRANSPONDER, Active_TRANSPONDER, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.   |�
����  �    Status                           ~� -   �  �    Object Handle                    �= - � �  �    Error Info                       �i -� �  �    Var_transponder                  �� �     �    Arg2                               	                       NULL    ""    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    U    An ActiveX object handle obtained from New_TRANSPONDER, Open_TRANSPONDER, Active_TRANSPONDER, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.   �p
����  �    Status                           �� -   �  �    Object Handle                    �� - � �  �    Error Info                       � -� �  �    Modelo                           �~ �     �    Arg2                               	                       NULL    ""    	               A value indicating whether an error occurred.  A negative error code indicates function failure.

Error codes are defined in cvi\include\cviauto.h and cvi\sdk\include\winerror.h.

You can use CA_GetAutomationErrorString to get the description of an error code or CA_DisplayErrorInfo to display the description of the error code.

If the error code is DISP_E_EXCEPTION  (0x80020009 or -2147352567), then the Error Info parameter contains additional error information.  You can use CA_DisplayErrorInfo to display the error information.    U    An ActiveX object handle obtained from New_TRANSPONDER, Open_TRANSPONDER, Active_TRANSPONDER, or an ActiveX method or property.

All of the methods that can be applied to a particular object are grouped under a single class in the function tree.  The name of the class corresponds to the type of the object to which this handle must refer.    $    When an ActiveX server function fails with the error code DISP_E_EXCEPTION, descriptive information about the error code is stored in this parameter.  The descriptive information may include the error's code, source, and description.  It may also include a help file and help file context.

When an ActiveX server function fails with the error codes DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, or E_INVALIDARG, the parameter position of the invalid argument may be stored in the errorParamPos member of this parameter.

This parameter may be NULL.     ^    Documentation for this function, if provided by the server, is located in the function help.     ^    Documentation for this function, if provided by the server, is located in the function help.    ^    Documentation for this function, if provided by the server, is located in the function help.

The string passed in this parameter must be allocated by calling the CVI ActiveX Library function CA_AllocMemory.

When it is no longer needed, the string returned in this parameter must be freed by calling the CVI ActiveX Library function CA_FreeMemory.     ^    Documentation for this function, if provided by the server, is located in the function help.   �
����  �    Status                           �> -   �  �    Object Handle                    �� - � �  �    Error Info                       �� -� �  �    Var_transponder                  �- �  �  �    Numserie                         �� � �    �    Nserie                           �� ��    �    Arg4                               	                       NULL    ""    ""    	            	         ����         �  r             K.        New_SMF                                                                                                                                 ����         �               K.        Open_SMF                                                                                                                                ����         �  !�             K.        Active_SMF                                                                                                                              ����       ����  )
             K.        _SMFGetmy_sockID                                                                                                                        ����       ����  0              K.        _SMFSetmy_sockID                                                                                                                        ����       ����  6�             K.        _SMFGetmy_BaseTimestamp                                                                                                                 ����       ����  =�             K.        _SMFSetmy_BaseTimestamp                                                                                                                 ����       ����  EZ             K.        _SMFGetmy_BaseData                                                                                                                      ����       ����  LP             K.        _SMFSetmy_BaseData                                                                                                                      ����       ����  S�             K.        _SMFGetmy_Station_ID                                                                                                                    ����       ����  Z�             K.        _SMFSetmy_Station_ID                                                                                                                    ����       ����  a�             K.        _SMFGetmy_Timeout                                                                                                                       ����       ����  h�             K.        _SMFSetmy_Timeout                                                                                                                       ����       ����  qL             K.        _SMFreadini                                                                                                                             ����       ����  z�             K.        _SMFwriteini                                                                                                                            ����       ����  ��             K.        _SMFopen_sock                                                                                                                           ����       ����  �v             K.        _SMFsync_sock                                                                                                                           ����       ����  ��             K.        _SMFclose_sock                                                                                                                          ����       ����  �;             K.        _SMFerrormsg                                                                                                                            ����       ����  �h         	    K.        _SMFmoveout                                                                                                                             ����       ����  �         	    K.        _SMFmovein                                                                                                                              ����       ����  �         
    K.        _SMFpackout                                                                                                                             ����       ����  �e             K.        _SMFenvtest                                                                                                                             ����       ����  �)             K.        _SMFSMFMessage                                                                                                                          ����       ����  �         	    K.        _SMFBuild                                                                                                                               ����       ����  �         
    K.        _SMFoperator                                                                                                                            ����       ����  ��             K.        _SMFenvtestgroup                                                                                                                        ����         �B �             K.        New_Comm                                                                                                                                ����        w �             K.        Open_Comm                                                                                                                               ����        P '             K.        Active_Comm                                                                                                                             ����       ���� %f             K.        _CommOpenCOM                                                                                                                            ����       ���� ,�             K.        _CommCloseCOM                                                                                                                           ����       ���� 52             K.        _CommReadCOM                                                                                                                            ����       ���� <�             K.        _CommWriteCOM                                                                                                                           ����        > G�             K.        New_TRANSPONDER                                                                                                                         ����        II Sv             K.        Open_TRANSPONDER                                                                                                                        ����        U) ^             K.        Active_TRANSPONDER                                                                                                                      ����       ���� g�             K.        _TRANSPONDERLeitura                                                                                                                     ����       ���� q�             K.        _TRANSPONDERInicializa                                                                                                                  ����       ���� {E             K.        _TRANSPONDERRecupera                                                                                                                    ����       ���� �5             K.        _TRANSPONDERLimpa                                                                                                                       ����       ���� ��             K.        _TRANSPONDERRegride                                                                                                                     ����       ���� �_             K.        _TRANSPONDERAssocia                                                                                                                         ����                                                                                  ����_SMF                                                                                 �New _SMF                                                                             �Open _SMF                                                                            �Active _SMF                                                                          �Getmy_sock ID                                                                        �Setmy_sock ID                                                                        �Getmy_Base Timestamp                                                                 �Setmy_Base Timestamp                                                                 �Getmy_Base Data                                                                      �Setmy_Base Data                                                                      �Getmy_Station_ID                                                                     �Setmy_Station_ID                                                                     �Getmy_Timeout                                                                        �Setmy_Timeout                                                                        �Readini                                                                              �Writeini                                                                             �Open_sock                                                                            �Sync_sock                                                                            �Close_sock                                                                           �Errormsg                                                                             �Moveout                                                                              �Movein                                                                               �Packout                                                                              �Envtest                                                                              �SMF Message                                                                          �Build                                                                                �Operator                                                                             �Envtestgroup                                                                      ����_Comm                                                                                �New _Comm                                                                            �Open _Comm                                                                           �Active _Comm                                                                         �Open COM                                                                             �Close COM                                                                            �Read COM                                                                             �Write COM                                                                         ����_TRANSPONDER                                                                         �New _TRANSPONDER                                                                     �Open _TRANSPONDER                                                                    �Active _TRANSPONDER                                                                  �Leitura                                                                              �Inicializa                                                                           �Recupera                                                                             �Limpa                                                                                �Regride                                                                              �Associa                                                                         