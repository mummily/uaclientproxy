/******************************************************************************
** uaenumdefinitiondatatype.h
**
** Copyright (c) 2006-2018 Unified Automation GmbH All rights reserved.
**
** Software License Agreement ("SLA") Version 2.7
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.7, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.7/
**
** Project: C++ OPC SDK base module
**
** Portable UaEnumDefinitionDataType class.
**
******************************************************************************/
#ifndef UAENUMDEFINITIONDATATYPE_H
#define UAENUMDEFINITIONDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaenumfield.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaEnumDefinitionDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_EnumDefinition.
 *
 *  This class encapsulates the native OpcUa_EnumDefinition structure
 *  and handles memory allocation and cleanup for you.
 *  UaEnumDefinitionDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared EnumDefinitionDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaEnumDefinitionDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaEnumDefinitionDataType
{
    UA_DECLARE_PRIVATE(UaEnumDefinitionDataType)
public:
    UaEnumDefinitionDataType();
    UaEnumDefinitionDataType(const UaEnumDefinitionDataType &other);
    UaEnumDefinitionDataType(const OpcUa_EnumDefinition &other);
    UaEnumDefinitionDataType(
        const UaEnumFields &fields
        );
    UaEnumDefinitionDataType(const UaExtensionObject &extensionObject);
    UaEnumDefinitionDataType(const OpcUa_ExtensionObject &extensionObject);
    UaEnumDefinitionDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaEnumDefinitionDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaEnumDefinitionDataType();

    void clear();

    bool operator==(const UaEnumDefinitionDataType &other) const;
    bool operator!=(const UaEnumDefinitionDataType &other) const;

    UaEnumDefinitionDataType& operator=(const UaEnumDefinitionDataType &other);

    OpcUa_EnumDefinition* copy() const;
    void copyTo(OpcUa_EnumDefinition *pDst) const;

    static OpcUa_EnumDefinition* clone(const OpcUa_EnumDefinition& source);
    static void cloneTo(const OpcUa_EnumDefinition& source, OpcUa_EnumDefinition& copy);

    void attach(OpcUa_EnumDefinition *pValue);
    OpcUa_EnumDefinition* detach(OpcUa_EnumDefinition* pDst);

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    void toExtensionObject(UaExtensionObject &extensionObject) const;
    void toExtensionObject(OpcUa_ExtensionObject &extensionObject) const;
    void toExtensionObject(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    void toExtensionObject(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    OpcUa_StatusCode setEnumDefinition(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setEnumDefinition(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setEnumDefinition(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumDefinition(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setEnumDefinition(
        const UaEnumFields &fields
        );

    void getFields(UaEnumFields& fields) const;

    void setFields(const UaEnumFields &fields);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_EnumDefinition.
 *
 *  This class encapsulates an array of the native OpcUa_EnumDefinition structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaEnumDefinitionDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaEnumDefinitionDataTypes
{
public:
    UaEnumDefinitionDataTypes();
    UaEnumDefinitionDataTypes(const UaEnumDefinitionDataTypes &other);
    UaEnumDefinitionDataTypes(OpcUa_Int32 length, OpcUa_EnumDefinition* data);
    virtual ~UaEnumDefinitionDataTypes();

    UaEnumDefinitionDataTypes& operator=(const UaEnumDefinitionDataTypes &other);
    const OpcUa_EnumDefinition& operator[](OpcUa_UInt32 index) const;
    OpcUa_EnumDefinition& operator[](OpcUa_UInt32 index);

    bool operator==(const UaEnumDefinitionDataTypes &other) const;
    bool operator!=(const UaEnumDefinitionDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_EnumDefinition* data);
    void attach(OpcUa_Int32 length, OpcUa_EnumDefinition* data);
    OpcUa_EnumDefinition* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_EnumDefinition* rawData() const {return m_data;}
    inline OpcUa_EnumDefinition* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setEnumDefinitions(const UaVariant &variant);
    OpcUa_StatusCode setEnumDefinitions(const OpcUa_Variant &variant);
    OpcUa_StatusCode setEnumDefinitions(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumDefinitions(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumDefinitions(OpcUa_Int32 length, OpcUa_EnumDefinition* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_EnumDefinition* m_data;
};

#endif // UAENUMDEFINITIONDATATYPE_H

