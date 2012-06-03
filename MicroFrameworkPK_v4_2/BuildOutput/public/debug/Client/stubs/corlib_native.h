//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------


#ifndef _CORLIB_NATIVE_H_
#define _CORLIB_NATIVE_H_

struct Library_corlib_native_System_Object
{
    TINYCLR_NATIVE_DECLARE(Equals___BOOLEAN__OBJECT);
    TINYCLR_NATIVE_DECLARE(GetHashCode___I4);
    TINYCLR_NATIVE_DECLARE(GetType___SystemType);
    TINYCLR_NATIVE_DECLARE(MemberwiseClone___OBJECT);
    TINYCLR_NATIVE_DECLARE(ReferenceEquals___STATIC__BOOLEAN__OBJECT__OBJECT);

    //--//

};

struct Library_corlib_native__<PrivateImplementationDetails>{932C1D83-5705-4533-919A-1CDDEB9C61A6}
{
    static const int FIELD_STATIC__$$method0x60003e4-1 = 0;
    static const int FIELD_STATIC__$$method0x60003e4-2 = 1;


    //--//

};

struct Library_corlib_native_System_ValueType
{
    TINYCLR_NATIVE_DECLARE(Equals___BOOLEAN__OBJECT);

    //--//

};

struct Library_corlib_native_System_Collections_Hashtable
{
    static const int FIELD___buckets = 1;
    static const int FIELD___numberOfBuckets = 2;
    static const int FIELD___count = 3;
    static const int FIELD___loadFactor = 4;
    static const int FIELD___maxLoadFactor = 5;
    static const int FIELD___growthFactor = 6;


    //--//

};

struct Library_corlib_native_System_Collections_Hashtable__Entry
{
    static const int FIELD__key = 1;
    static const int FIELD__value = 2;
    static const int FIELD__next = 3;


    //--//

};

struct Library_corlib_native_System_Collections_Hashtable__HashtableEnumerator
{
    static const int FIELD__ht = 1;
    static const int FIELD__temp = 2;
    static const int FIELD__index = 3;
    static const int FIELD__returnType = 4;


    //--//

};

struct Library_corlib_native_System_Exception
{
    static const int FIELD___message = 1;
    static const int FIELD__m_innerException = 2;
    static const int FIELD__m_stackTrace = 3;
    static const int FIELD__m_HResult = 4;

    TINYCLR_NATIVE_DECLARE(get_StackTrace___STRING);

    //--//

};

struct Library_corlib_native_System_Collections_Hashtable__KeyCollection
{
    static const int FIELD__ht = 1;


    //--//

};

struct Library_corlib_native_System_Array
{
    TINYCLR_NATIVE_DECLARE(System_Collections_IList_get_Item___OBJECT__I4);
    TINYCLR_NATIVE_DECLARE(System_Collections_IList_set_Item___VOID__I4__OBJECT);
    TINYCLR_NATIVE_DECLARE(get_Length___I4);
    TINYCLR_NATIVE_DECLARE(CreateInstance___STATIC__SystemArray__SystemType__I4);
    TINYCLR_NATIVE_DECLARE(Copy___STATIC__VOID__SystemArray__I4__SystemArray__I4__I4);
    TINYCLR_NATIVE_DECLARE(Clear___STATIC__VOID__SystemArray__I4__I4);
    TINYCLR_NATIVE_DECLARE(TrySZIndexOf___STATIC__BOOLEAN__SystemArray__I4__I4__OBJECT__BYREF_I4);

    //--//

};

struct Library_corlib_native_System_Array__SZArrayEnumerator
{
    static const int FIELD___array = 1;
    static const int FIELD___index = 2;
    static const int FIELD___endIndex = 3;
    static const int FIELD___startIndex = 4;
    static const int FIELD___arrayLength = 5;


    //--//

};

struct Library_corlib_native_System_Globalization_Resources_CultureInfo
{
    static const int FIELD_STATIC__manager = 2;


    //--//

};

struct Library_corlib_native_System_AppDomain
{
    static const int FIELD__m_appDomain = 1;
    static const int FIELD__m_friendlyName = 2;

    TINYCLR_NATIVE_DECLARE(GetAssemblies___SZARRAY_SystemReflectionAssembly);
    TINYCLR_NATIVE_DECLARE(LoadInternal___SystemReflectionAssembly__STRING__BOOLEAN__I4__I4__I4__I4);
    TINYCLR_NATIVE_DECLARE(CreateDomain___STATIC__SystemAppDomain__STRING);
    TINYCLR_NATIVE_DECLARE(Unload___STATIC__VOID__SystemAppDomain);

    //--//

};

struct Library_corlib_native_System_ArgumentException
{
    static const int FIELD__m_paramName = 5;


    //--//

};

struct Library_corlib_native_System_Delegate
{
    TINYCLR_NATIVE_DECLARE(Equals___BOOLEAN__OBJECT);
    TINYCLR_NATIVE_DECLARE(get_Method___SystemReflectionMethodInfo);
    TINYCLR_NATIVE_DECLARE(get_Target___OBJECT);
    TINYCLR_NATIVE_DECLARE(Combine___STATIC__SystemDelegate__SystemDelegate__SystemDelegate);
    TINYCLR_NATIVE_DECLARE(Remove___STATIC__SystemDelegate__SystemDelegate__SystemDelegate);
    TINYCLR_NATIVE_DECLARE(op_Equality___STATIC__BOOLEAN__SystemDelegate__SystemDelegate);
    TINYCLR_NATIVE_DECLARE(op_Inequality___STATIC__BOOLEAN__SystemDelegate__SystemDelegate);

    //--//

};

struct Library_corlib_native_System_MulticastDelegate
{
    TINYCLR_NATIVE_DECLARE(op_Equality___STATIC__BOOLEAN__SystemMulticastDelegate__SystemMulticastDelegate);
    TINYCLR_NATIVE_DECLARE(op_Inequality___STATIC__BOOLEAN__SystemMulticastDelegate__SystemMulticastDelegate);

    //--//

};

struct Library_corlib_native_System_Boolean
{
    static const int FIELD_STATIC__FalseString = 3;
    static const int FIELD_STATIC__TrueString = 4;

    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Byte
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Char
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Collections_ArrayList
{
    static const int FIELD___items = 1;
    static const int FIELD___size = 2;

    TINYCLR_NATIVE_DECLARE(get_Item___OBJECT__I4);
    TINYCLR_NATIVE_DECLARE(set_Item___VOID__I4__OBJECT);
    TINYCLR_NATIVE_DECLARE(Add___I4__OBJECT);
    TINYCLR_NATIVE_DECLARE(Clear___VOID);
    TINYCLR_NATIVE_DECLARE(Insert___VOID__I4__OBJECT);
    TINYCLR_NATIVE_DECLARE(RemoveAt___VOID__I4);
    TINYCLR_NATIVE_DECLARE(SetCapacity___VOID__I4);

    //--//

};

struct Library_corlib_native_System_Collections_DictionaryEntry
{
    static const int FIELD__Key = 1;
    static const int FIELD__Value = 2;


    //--//

};

struct Library_corlib_native_System_Collections_Queue
{
    static const int FIELD___array = 1;
    static const int FIELD___head = 2;
    static const int FIELD___tail = 3;
    static const int FIELD___size = 4;

    TINYCLR_NATIVE_DECLARE(Clear___VOID);
    TINYCLR_NATIVE_DECLARE(CopyTo___VOID__SystemArray__I4);
    TINYCLR_NATIVE_DECLARE(Enqueue___VOID__OBJECT);
    TINYCLR_NATIVE_DECLARE(Dequeue___OBJECT);
    TINYCLR_NATIVE_DECLARE(Peek___OBJECT);

    //--//

};

struct Library_corlib_native_System_Collections_Stack
{
    static const int FIELD___array = 1;
    static const int FIELD___size = 2;

    TINYCLR_NATIVE_DECLARE(Clear___VOID);
    TINYCLR_NATIVE_DECLARE(Peek___OBJECT);
    TINYCLR_NATIVE_DECLARE(Pop___OBJECT);
    TINYCLR_NATIVE_DECLARE(Push___VOID__OBJECT);

    //--//

};

struct Library_corlib_native_System_Convert
{
    static const int FIELD_STATIC__s_rgchBase64Encoding = 5;
    static const int FIELD_STATIC__s_rgbBase64Decode = 6;


    //--//

};

struct Library_corlib_native_System_TimeZone
{
    static const int FIELD__m_id = 1;

    TINYCLR_NATIVE_DECLARE(GetTimeZoneOffset___STATIC__I8);

    //--//

};

struct Library_corlib_native_System_CurrentSystemTimeZone
{
    static const int FIELD__m_ticksOffset = 2;


    //--//

};

struct Library_corlib_native_System_DateTime
{
    static const int FIELD_STATIC__MinValue = 7;
    static const int FIELD_STATIC__MaxValue = 8;
    static const int FIELD_STATIC__ticksAtOrigin = 9;

    static const int FIELD__m_ticks = 1;

    TINYCLR_NATIVE_DECLARE(_ctor___VOID__I4__I4__I4__I4__I4__I4__I4);
    TINYCLR_NATIVE_DECLARE(get_Day___I4);
    TINYCLR_NATIVE_DECLARE(get_DayOfWeek___SystemDayOfWeek);
    TINYCLR_NATIVE_DECLARE(get_DayOfYear___I4);
    TINYCLR_NATIVE_DECLARE(get_Hour___I4);
    TINYCLR_NATIVE_DECLARE(get_Millisecond___I4);
    TINYCLR_NATIVE_DECLARE(get_Minute___I4);
    TINYCLR_NATIVE_DECLARE(get_Month___I4);
    TINYCLR_NATIVE_DECLARE(get_Second___I4);
    TINYCLR_NATIVE_DECLARE(get_Year___I4);
    TINYCLR_NATIVE_DECLARE(ToLocalTime___SystemDateTime);
    TINYCLR_NATIVE_DECLARE(ToUniversalTime___SystemDateTime);
    TINYCLR_NATIVE_DECLARE(DaysInMonth___STATIC__I4__I4__I4);
    TINYCLR_NATIVE_DECLARE(get_Now___STATIC__SystemDateTime);
    TINYCLR_NATIVE_DECLARE(get_UtcNow___STATIC__SystemDateTime);
    TINYCLR_NATIVE_DECLARE(get_Today___STATIC__SystemDateTime);

    //--//

};

struct Library_corlib_native_System_Diagnostics_Debugger
{
    TINYCLR_NATIVE_DECLARE(get_IsAttached___STATIC__BOOLEAN);
    TINYCLR_NATIVE_DECLARE(Break___STATIC__VOID);

    //--//

};

struct Library_corlib_native_System_Double
{
    static const int FIELD__m_value = 1;

    TINYCLR_NATIVE_DECLARE(CompareTo___STATIC__I4__R8__R8);
    TINYCLR_NATIVE_DECLARE(IsInfinity___STATIC__BOOLEAN__R8);
    TINYCLR_NATIVE_DECLARE(IsNaN___STATIC__BOOLEAN__R8);
    TINYCLR_NATIVE_DECLARE(IsNegativeInfinity___STATIC__BOOLEAN__R8);
    TINYCLR_NATIVE_DECLARE(IsPositiveInfinity___STATIC__BOOLEAN__R8);

    //--//

};

struct Library_corlib_native_System_GC
{
    TINYCLR_NATIVE_DECLARE(AnyPendingFinalizers___STATIC__BOOLEAN);
    TINYCLR_NATIVE_DECLARE(SuppressFinalize___STATIC__VOID__OBJECT);
    TINYCLR_NATIVE_DECLARE(ReRegisterForFinalize___STATIC__VOID__OBJECT);

    //--//

};

struct Library_corlib_native_System_Globalization_CultureInfo
{
    static const int FIELD__numInfo = 1;
    static const int FIELD__dateTimeInfo = 2;
    static const int FIELD__m_name = 3;
    static const int FIELD__m_rm = 4;
    static const int FIELD__m_parent = 5;

    TINYCLR_NATIVE_DECLARE(get_CurrentUICultureInternal___STATIC__SystemGlobalizationCultureInfo);
    TINYCLR_NATIVE_DECLARE(set_CurrentUICultureInternal___STATIC__VOID__SystemGlobalizationCultureInfo);

    //--//

};

struct Library_corlib_native_System_Globalization_DateTimeFormat
{
    TINYCLR_NATIVE_DECLARE(FormatDigits___STATIC__STRING__I4__I4);

    //--//

};

struct Library_corlib_native_System_Globalization_DateTimeFormatInfo
{
    static const int FIELD__amDesignator = 1;
    static const int FIELD__pmDesignator = 2;
    static const int FIELD__dateSeparator = 3;
    static const int FIELD__longTimePattern = 4;
    static const int FIELD__shortTimePattern = 5;
    static const int FIELD__generalShortTimePattern = 6;
    static const int FIELD__generalLongTimePattern = 7;
    static const int FIELD__timeSeparator = 8;
    static const int FIELD__monthDayPattern = 9;
    static const int FIELD__fullDateTimePattern = 10;
    static const int FIELD__longDatePattern = 11;
    static const int FIELD__shortDatePattern = 12;
    static const int FIELD__yearMonthPattern = 13;
    static const int FIELD__abbreviatedDayNames = 14;
    static const int FIELD__dayNames = 15;
    static const int FIELD__abbreviatedMonthNames = 16;
    static const int FIELD__monthNames = 17;
    static const int FIELD__m_cultureInfo = 18;


    //--//

};

struct Library_corlib_native_System_Globalization_DaylightTime
{
    static const int FIELD__m_start = 1;
    static const int FIELD__m_end = 2;
    static const int FIELD__m_delta = 3;


    //--//

};

struct Library_corlib_native_System_Globalization_NumberFormatInfo
{
    static const int FIELD__numberGroupSizes = 1;
    static const int FIELD__positiveSign = 2;
    static const int FIELD__negativeSign = 3;
    static const int FIELD__numberDecimalSeparator = 4;
    static const int FIELD__numberGroupSeparator = 5;
    static const int FIELD__m_cultureInfo = 6;


    //--//

};

struct Library_corlib_native_System_Guid
{
    static const int FIELD_STATIC__m_rand = 10;
    static const int FIELD_STATIC__Empty = 11;

    static const int FIELD__m_data = 1;


    //--//

};

struct Library_corlib_native_System_Int16
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Int32
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Int64
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Math
{
    TINYCLR_NATIVE_DECLARE(Acos___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Asin___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Atan___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Atan2___STATIC__R8__R8__R8);
    TINYCLR_NATIVE_DECLARE(Ceiling___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Cos___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Cosh___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(IEEERemainder___STATIC__R8__R8__R8);
    TINYCLR_NATIVE_DECLARE(Exp___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Floor___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Log___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Log10___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Pow___STATIC__R8__R8__R8);
    TINYCLR_NATIVE_DECLARE(Round___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Sign___STATIC__I4__R8);
    TINYCLR_NATIVE_DECLARE(Sin___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Sinh___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Sqrt___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Tan___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Tanh___STATIC__R8__R8);
    TINYCLR_NATIVE_DECLARE(Truncate___STATIC__R8__R8);

    //--//

};

struct Library_corlib_native_System_Number
{
    TINYCLR_NATIVE_DECLARE(FormatNative___STATIC__STRING__OBJECT__CHAR__I4);

    //--//

};

struct Library_corlib_native_System_Random
{
    static const int FIELD___random = 1;

    TINYCLR_NATIVE_DECLARE(Next___I4);
    TINYCLR_NATIVE_DECLARE(Next___I4__I4);
    TINYCLR_NATIVE_DECLARE(NextDouble___R8);
    TINYCLR_NATIVE_DECLARE(NextBytes___VOID__SZARRAY_U1);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__I4);

    //--//

};

struct Library_corlib_native_System_Reflection_Assembly
{
    TINYCLR_NATIVE_DECLARE(get_FullName___STRING);
    TINYCLR_NATIVE_DECLARE(GetType___SystemType__STRING);
    TINYCLR_NATIVE_DECLARE(GetTypes___SZARRAY_SystemType);
    TINYCLR_NATIVE_DECLARE(GetVersion___VOID__BYREF_I4__BYREF_I4__BYREF_I4__BYREF_I4);
    TINYCLR_NATIVE_DECLARE(GetManifestResourceNames___SZARRAY_STRING);
    TINYCLR_NATIVE_DECLARE(GetExecutingAssembly___STATIC__SystemReflectionAssembly);
    TINYCLR_NATIVE_DECLARE(LoadInternal___STATIC__SystemReflectionAssembly__STRING__BOOLEAN__I4__I4__I4__I4);
    TINYCLR_NATIVE_DECLARE(Load___STATIC__SystemReflectionAssembly__SZARRAY_U1);

    //--//

};

struct Library_corlib_native_System_Reflection_AssemblyName
{
    static const int FIELD___assembly = 1;


    //--//

};

struct Library_corlib_native_System_Reflection_MethodBase
{
    TINYCLR_NATIVE_DECLARE(get_Name___STRING);
    TINYCLR_NATIVE_DECLARE(get_DeclaringType___SystemType);
    TINYCLR_NATIVE_DECLARE(get_IsPublic___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsStatic___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsFinal___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsVirtual___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsAbstract___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(Invoke___OBJECT__OBJECT__SZARRAY_OBJECT);

    //--//

};

struct Library_corlib_native_System_Reflection_ConstructorInfo
{
    TINYCLR_NATIVE_DECLARE(Invoke___OBJECT__SZARRAY_OBJECT);

    //--//

};

struct Library_corlib_native_System_Reflection_FieldInfo
{
    TINYCLR_NATIVE_DECLARE(SetValue___VOID__OBJECT__OBJECT);

    //--//

};

struct Library_corlib_native_System_Reflection_PropertyInfo
{
    TINYCLR_NATIVE_DECLARE(GetValue___OBJECT__OBJECT__SZARRAY_OBJECT);
    TINYCLR_NATIVE_DECLARE(SetValue___VOID__OBJECT__OBJECT__SZARRAY_OBJECT);

    //--//

};

struct Library_corlib_native_System_Reflection_RuntimeFieldInfo
{
    TINYCLR_NATIVE_DECLARE(get_Name___STRING);
    TINYCLR_NATIVE_DECLARE(get_DeclaringType___SystemType);
    TINYCLR_NATIVE_DECLARE(get_FieldType___SystemType);
    TINYCLR_NATIVE_DECLARE(GetValue___OBJECT__OBJECT);

    //--//

};

struct Library_corlib_native_System_Reflection_RuntimeMethodInfo
{
    TINYCLR_NATIVE_DECLARE(get_ReturnType___SystemType);

    //--//

};

struct Library_corlib_native_System_Resources_ResourceManager
{
    static const int FIELD__m_resourceFileId = 1;
    static const int FIELD__m_assembly = 2;
    static const int FIELD__m_baseAssembly = 3;
    static const int FIELD__m_baseName = 4;
    static const int FIELD__m_cultureName = 5;
    static const int FIELD__m_rmFallback = 6;

    TINYCLR_NATIVE_DECLARE(GetObjectInternal___OBJECT__I2);
    TINYCLR_NATIVE_DECLARE(GetObjectInternal___OBJECT__I2__I4__I4);
    TINYCLR_NATIVE_DECLARE(FindResource___STATIC__I4__STRING__SystemReflectionAssembly);
    TINYCLR_NATIVE_DECLARE(GetObject___STATIC__OBJECT__SystemResourcesResourceManager__SystemEnum);

    //--//

};

struct Library_corlib_native_System_Runtime_CompilerServices_AccessedThroughPropertyAttribute
{
    static const int FIELD__propertyName = 1;


    //--//

};

struct Library_corlib_native_System_Runtime_CompilerServices_RuntimeHelpers
{
    TINYCLR_NATIVE_DECLARE(InitializeArray___STATIC__VOID__SystemArray__SystemRuntimeFieldHandle);
    TINYCLR_NATIVE_DECLARE(GetObjectValue___STATIC__OBJECT__OBJECT);
    TINYCLR_NATIVE_DECLARE(RunClassConstructor___STATIC__VOID__SystemRuntimeTypeHandle);
    TINYCLR_NATIVE_DECLARE(get_OffsetToStringData___STATIC__I4);

    //--//

};

struct Library_corlib_native_System_Runtime_Remoting_RemotingServices
{
    TINYCLR_NATIVE_DECLARE(IsTransparentProxy___STATIC__BOOLEAN__OBJECT);

    //--//

};

struct Library_corlib_native_System_Runtime_Versioning_TargetFrameworkAttribute
{
    static const int FIELD___frameworkName = 1;
    static const int FIELD___frameworkDisplayName = 2;


    //--//

};

struct Library_corlib_native_System_Type
{
    TINYCLR_NATIVE_DECLARE(get_DeclaringType___SystemType);
    TINYCLR_NATIVE_DECLARE(GetMethod___SystemReflectionMethodInfo__STRING__SystemReflectionBindingFlags);
    TINYCLR_NATIVE_DECLARE(IsInstanceOfType___BOOLEAN__OBJECT);
    TINYCLR_NATIVE_DECLARE(InvokeMember___OBJECT__STRING__SystemReflectionBindingFlags__SystemReflectionBinder__OBJECT__SZARRAY_OBJECT);
    TINYCLR_NATIVE_DECLARE(GetConstructor___SystemReflectionConstructorInfo__SZARRAY_SystemType);
    TINYCLR_NATIVE_DECLARE(GetMethod___SystemReflectionMethodInfo__STRING__SZARRAY_SystemType);
    TINYCLR_NATIVE_DECLARE(GetMethod___SystemReflectionMethodInfo__STRING);
    TINYCLR_NATIVE_DECLARE(get_IsNotPublic___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsPublic___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsClass___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsInterface___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsValueType___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsAbstract___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsEnum___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsSerializable___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_IsArray___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(GetTypeInternal___STATIC__SystemType__STRING__STRING__BOOLEAN__SZARRAY_I4);
    TINYCLR_NATIVE_DECLARE(GetTypeFromHandle___STATIC__SystemType__SystemRuntimeTypeHandle);

    //--//

};

struct Library_corlib_native_System_RuntimeType
{
    TINYCLR_NATIVE_DECLARE(get_Assembly___SystemReflectionAssembly);
    TINYCLR_NATIVE_DECLARE(get_Name___STRING);
    TINYCLR_NATIVE_DECLARE(get_FullName___STRING);
    TINYCLR_NATIVE_DECLARE(get_BaseType___SystemType);
    TINYCLR_NATIVE_DECLARE(GetMethods___SZARRAY_SystemReflectionMethodInfo__SystemReflectionBindingFlags);
    TINYCLR_NATIVE_DECLARE(GetField___SystemReflectionFieldInfo__STRING__SystemReflectionBindingFlags);
    TINYCLR_NATIVE_DECLARE(GetFields___SZARRAY_SystemReflectionFieldInfo__SystemReflectionBindingFlags);
    TINYCLR_NATIVE_DECLARE(GetInterfaces___SZARRAY_SystemType);
    TINYCLR_NATIVE_DECLARE(GetElementType___SystemType);

    //--//

};

struct Library_corlib_native_System_SByte
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Single
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_String
{
    static const int FIELD_STATIC__Empty = 12;

    TINYCLR_NATIVE_DECLARE(CompareTo___I4__OBJECT);
    TINYCLR_NATIVE_DECLARE(get_Chars___CHAR__I4);
    TINYCLR_NATIVE_DECLARE(ToCharArray___SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(ToCharArray___SZARRAY_CHAR__I4__I4);
    TINYCLR_NATIVE_DECLARE(get_Length___I4);
    TINYCLR_NATIVE_DECLARE(Split___SZARRAY_STRING__SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(Split___SZARRAY_STRING__SZARRAY_CHAR__I4);
    TINYCLR_NATIVE_DECLARE(Substring___STRING__I4);
    TINYCLR_NATIVE_DECLARE(Substring___STRING__I4__I4);
    TINYCLR_NATIVE_DECLARE(Trim___STRING__SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(TrimStart___STRING__SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(TrimEnd___STRING__SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__SZARRAY_CHAR__I4__I4);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__CHAR__I4);
    TINYCLR_NATIVE_DECLARE(CompareTo___I4__STRING);
    TINYCLR_NATIVE_DECLARE(IndexOf___I4__CHAR);
    TINYCLR_NATIVE_DECLARE(IndexOf___I4__CHAR__I4);
    TINYCLR_NATIVE_DECLARE(IndexOf___I4__CHAR__I4__I4);
    TINYCLR_NATIVE_DECLARE(IndexOfAny___I4__SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(IndexOfAny___I4__SZARRAY_CHAR__I4);
    TINYCLR_NATIVE_DECLARE(IndexOfAny___I4__SZARRAY_CHAR__I4__I4);
    TINYCLR_NATIVE_DECLARE(IndexOf___I4__STRING);
    TINYCLR_NATIVE_DECLARE(IndexOf___I4__STRING__I4);
    TINYCLR_NATIVE_DECLARE(IndexOf___I4__STRING__I4__I4);
    TINYCLR_NATIVE_DECLARE(LastIndexOf___I4__CHAR);
    TINYCLR_NATIVE_DECLARE(LastIndexOf___I4__CHAR__I4);
    TINYCLR_NATIVE_DECLARE(LastIndexOf___I4__CHAR__I4__I4);
    TINYCLR_NATIVE_DECLARE(LastIndexOfAny___I4__SZARRAY_CHAR);
    TINYCLR_NATIVE_DECLARE(LastIndexOfAny___I4__SZARRAY_CHAR__I4);
    TINYCLR_NATIVE_DECLARE(LastIndexOfAny___I4__SZARRAY_CHAR__I4__I4);
    TINYCLR_NATIVE_DECLARE(LastIndexOf___I4__STRING);
    TINYCLR_NATIVE_DECLARE(LastIndexOf___I4__STRING__I4);
    TINYCLR_NATIVE_DECLARE(LastIndexOf___I4__STRING__I4__I4);
    TINYCLR_NATIVE_DECLARE(ToLower___STRING);
    TINYCLR_NATIVE_DECLARE(ToUpper___STRING);
    TINYCLR_NATIVE_DECLARE(Trim___STRING);
    TINYCLR_NATIVE_DECLARE(Equals___STATIC__BOOLEAN__STRING__STRING);
    TINYCLR_NATIVE_DECLARE(op_Equality___STATIC__BOOLEAN__STRING__STRING);
    TINYCLR_NATIVE_DECLARE(op_Inequality___STATIC__BOOLEAN__STRING__STRING);
    TINYCLR_NATIVE_DECLARE(Compare___STATIC__I4__STRING__STRING);
    TINYCLR_NATIVE_DECLARE(Concat___STATIC__STRING__STRING__STRING);
    TINYCLR_NATIVE_DECLARE(Concat___STATIC__STRING__STRING__STRING__STRING);
    TINYCLR_NATIVE_DECLARE(Concat___STATIC__STRING__STRING__STRING__STRING__STRING);
    TINYCLR_NATIVE_DECLARE(Concat___STATIC__STRING__SZARRAY_STRING);

    //--//

};

struct Library_corlib_native_System_Text_StringBuilder
{
    static const int FIELD__m_MaxCapacity = 1;
    static const int FIELD__m_ChunkChars = 2;
    static const int FIELD__m_ChunkLength = 3;
    static const int FIELD__m_ChunkPrevious = 4;
    static const int FIELD__m_ChunkOffset = 5;


    //--//

};

struct Library_corlib_native_System_Text_UTF8Decoder
{
    TINYCLR_NATIVE_DECLARE(Convert___VOID__SZARRAY_U1__I4__I4__SZARRAY_CHAR__I4__I4__BOOLEAN__BYREF_I4__BYREF_I4__BYREF_BOOLEAN);

    //--//

};

struct Library_corlib_native_System_Text_UTF8Encoding
{
    TINYCLR_NATIVE_DECLARE(GetBytes___SZARRAY_U1__STRING);
    TINYCLR_NATIVE_DECLARE(GetBytes___I4__STRING__I4__I4__SZARRAY_U1__I4);
    TINYCLR_NATIVE_DECLARE(GetChars___SZARRAY_CHAR__SZARRAY_U1);
    TINYCLR_NATIVE_DECLARE(GetChars___SZARRAY_CHAR__SZARRAY_U1__I4__I4);

    //--//

};

struct Library_corlib_native_System_Threading_WaitHandle
{
    TINYCLR_NATIVE_DECLARE(WaitOne___BOOLEAN__I4__BOOLEAN);
    TINYCLR_NATIVE_DECLARE(WaitMultiple___STATIC__I4__SZARRAY_SystemThreadingWaitHandle__I4__BOOLEAN__BOOLEAN);

    //--//

};

struct Library_corlib_native_System_Threading_AutoResetEvent
{
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__BOOLEAN);
    TINYCLR_NATIVE_DECLARE(Reset___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(Set___BOOLEAN);

    //--//

};

struct Library_corlib_native_System_Threading_Interlocked
{
    TINYCLR_NATIVE_DECLARE(Increment___STATIC__I4__BYREF_I4);
    TINYCLR_NATIVE_DECLARE(Decrement___STATIC__I4__BYREF_I4);
    TINYCLR_NATIVE_DECLARE(Exchange___STATIC__I4__BYREF_I4__I4);
    TINYCLR_NATIVE_DECLARE(CompareExchange___STATIC__I4__BYREF_I4__I4__I4);

    //--//

};

struct Library_corlib_native_System_Threading_ManualResetEvent
{
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__BOOLEAN);
    TINYCLR_NATIVE_DECLARE(Reset___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(Set___BOOLEAN);

    //--//

};

struct Library_corlib_native_System_Threading_Monitor
{
    TINYCLR_NATIVE_DECLARE(Enter___STATIC__VOID__OBJECT);
    TINYCLR_NATIVE_DECLARE(Exit___STATIC__VOID__OBJECT);

    //--//

};

struct Library_corlib_native_System_Threading_Thread
{
    static const int FIELD__m_Delegate = 1;
    static const int FIELD__m_Priority = 2;
    static const int FIELD__m_Thread = 3;
    static const int FIELD__m_AppDomain = 4;
    static const int FIELD__m_Id = 5;

    TINYCLR_NATIVE_DECLARE(_ctor___VOID__SystemThreadingThreadStart);
    TINYCLR_NATIVE_DECLARE(Start___VOID);
    TINYCLR_NATIVE_DECLARE(Abort___VOID);
    TINYCLR_NATIVE_DECLARE(Suspend___VOID);
    TINYCLR_NATIVE_DECLARE(Resume___VOID);
    TINYCLR_NATIVE_DECLARE(get_Priority___SystemThreadingThreadPriority);
    TINYCLR_NATIVE_DECLARE(set_Priority___VOID__SystemThreadingThreadPriority);
    TINYCLR_NATIVE_DECLARE(get_ManagedThreadId___I4);
    TINYCLR_NATIVE_DECLARE(get_IsAlive___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(Join___VOID);
    TINYCLR_NATIVE_DECLARE(Join___BOOLEAN__I4);
    TINYCLR_NATIVE_DECLARE(Join___BOOLEAN__SystemTimeSpan);
    TINYCLR_NATIVE_DECLARE(get_ThreadState___SystemThreadingThreadState);
    TINYCLR_NATIVE_DECLARE(Sleep___STATIC__VOID__I4);
    TINYCLR_NATIVE_DECLARE(get_CurrentThread___STATIC__SystemThreadingThread);
    TINYCLR_NATIVE_DECLARE(GetDomain___STATIC__SystemAppDomain);

    //--//

};

struct Library_corlib_native_System_Threading_Timer
{
    static const int FIELD__m_timer = 1;
    static const int FIELD__m_state = 2;
    static const int FIELD__m_callback = 3;

    TINYCLR_NATIVE_DECLARE(Dispose___VOID);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__SystemThreadingTimerCallback__OBJECT__I4__I4);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__SystemThreadingTimerCallback__OBJECT__SystemTimeSpan__SystemTimeSpan);
    TINYCLR_NATIVE_DECLARE(Change___BOOLEAN__I4__I4);
    TINYCLR_NATIVE_DECLARE(Change___BOOLEAN__SystemTimeSpan__SystemTimeSpan);

    //--//

};

struct Library_corlib_native_System_TimeSpan
{
    static const int FIELD_STATIC__Zero = 13;
    static const int FIELD_STATIC__MaxValue = 14;
    static const int FIELD_STATIC__MinValue = 15;

    static const int FIELD__m_ticks = 1;

    TINYCLR_NATIVE_DECLARE(Equals___BOOLEAN__OBJECT);
    TINYCLR_NATIVE_DECLARE(ToString___STRING);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__I4__I4__I4);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__I4__I4__I4__I4);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__I4__I4__I4__I4__I4);
    TINYCLR_NATIVE_DECLARE(CompareTo___I4__OBJECT);
    TINYCLR_NATIVE_DECLARE(Compare___STATIC__I4__SystemTimeSpan__SystemTimeSpan);
    TINYCLR_NATIVE_DECLARE(Equals___STATIC__BOOLEAN__SystemTimeSpan__SystemTimeSpan);

    //--//

};

struct Library_corlib_native_System_UInt16
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_UInt32
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_UInt64
{
    static const int FIELD__m_value = 1;


    //--//

};

struct Library_corlib_native_System_Version
{
    static const int FIELD___Major = 1;
    static const int FIELD___Minor = 2;
    static const int FIELD___Build = 3;
    static const int FIELD___Revision = 4;


    //--//

};

struct Library_corlib_native_System_WeakReference
{
    TINYCLR_NATIVE_DECLARE(get_IsAlive___BOOLEAN);
    TINYCLR_NATIVE_DECLARE(get_Target___OBJECT);
    TINYCLR_NATIVE_DECLARE(set_Target___VOID__OBJECT);
    TINYCLR_NATIVE_DECLARE(_ctor___VOID__OBJECT);

    //--//

};

struct Library_corlib_native_System_Collections_Hashtable__ValueCollection
{
    static const int FIELD__ht = 1;


    //--//

};

#endif  //_CORLIB_NATIVE_H_
