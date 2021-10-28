/******************************************************************************
** uastructuredefinitiondatatype.h
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
** Portable UaStructureDefinitionDataType class.
**
******************************************************************************/
#ifndef UASTRUCTUREDEFINITIONDATATYPE_H
#define UASTRUCTUREDEFINITIONDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uanodeid.h"
#include "uastructurefielddatatype.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaStructureDefinitionDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_StructureDefinition.
 *
 *  This class encapsulates the native OpcUa_StructureDefinition structure
 *  and handles memory allocation and cleanup for you.
 *  UaStructureDefinitionDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared StructureDefinitionDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaStructureDefinitionDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaStructureDefinitionDataType
{
    UA_DECLARE_PRIVATE(UaStructureDefinitionDataType)
public:
    UaStructureDefinitionDataType();
    UaStructureDefinitionDataType(const UaStructureDefinitionDataType &other);
    UaStructureDefinitionDataType(const OpcUa_StructureDefinition &other);
    UaStructureDefinitionDataType(
        const UaNodeId& defaultEncodingId,
        const UaNodeId& baseDataType,
        OpcUa_StructureType structureType,
        const UaStructureFieldDataTypes &fields
        );
    UaStructureDefinitionDataType(const UaExtensionObject &extensionObject);
    UaStructureDefinitionDataType(const OpcUa_ExtensionObject &extensionObject);
    UaStructureDefinitionDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaStructureDefinitionDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaStructureDefinitionDataType();

    void clear();

    bool operator==(const UaStructureDefinitionDataType &other) const;
    bool operator!=(const UaStructureDefinitionDataType &other) const;

    UaStructureDefinitionDataType& operator=(const UaStructureDefinitionDataType &other);

    OpcUa_StructureDefinition* copy() const;
    void copyTo(OpcUa_StructureDefinition *pDst) const;

    static OpcUa_StructureDefinition* clone(const OpcUa_StructureDefinition& source);
    static void cloneTo(const OpcUa_StructureDefinition& source, OpcUa_StructureDefinition& copy);

    void attach(OpcUa_StructureDefinition *pValue);
    OpcUa_StructureDefinition* detach(OpcUa_StructureDefinition* pDst);

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

    OpcUa_StatusCode setStructureDefinition(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setStructureDefinition(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setStructureDefinition(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setStructureDefinition(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setStructureDefinition(
        const UaNodeId& defaultEncodingId,
        const UaNodeId& baseDataType,
        OpcUa_StructureType structureType,
        const UaStructureFieldDataTypes &fields
        );

    UaNodeId getDefaultEncodingId() const;
    UaNodeId getBaseDataType() const;
    OpcUa_StructureType getStructureType() const;
    void getFields(UaStructureFieldDataTypes& fields) const;

    void setDefaultEncodingId(const UaNodeId& defaultEncodingId);
    void setBaseDataType(const UaNodeId& baseDataType);
    void setStructureType(OpcUa_StructureType structureType);
    void setFields(const UaStructureFieldDataTypes &fields);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_StructureDefinition.
 *
 *  This class encapsulates an array of the native OpcUa_StructureDefinition structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaStructureDefinitionDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaStructureDefinitionDataTypes
{
public:
    UaStructureDefinitionDataTypes();
    UaStructureDefinitionDataTypes(const UaStructureDefinitionDataTypes &other);
    UaStructureDefinitionDataTypes(OpcUa_Int32 length, OpcUa_StructureDefinition* data);
    virtual ~UaStructureDefinitionDataTypes();

    UaStructureDefinitionDataTypes& operator=(const UaStructureDefinitionDataTypes &other);
    const OpcUa_StructureDefinition& operator[](OpcUa_UInt32 index) const;
    OpcUa_StructureDefinition& operator[](OpcUa_UInt32 index);

    bool operator==(const UaStructureDefinitionDataTypes &other) const;
    bool operator!=(const UaStructureDefinitionDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_StructureDefinition* data);
    void attach(OpcUa_Int32 length, OpcUa_StructureDefinition* data);
    OpcUa_StructureDefinition* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_StructureDefinition* rawData() const {return m_data;}
    inline OpcUa_StructureDefinition* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setStructureDefinitions(const UaVariant &variant);
    OpcUa_StatusCode setStructureDefinitions(const OpcUa_Variant &variant);
    OpcUa_StatusCode setStructureDefinitions(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setStructureDefinitions(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setStructureDefinitions(OpcUa_Int32 length, OpcUa_StructureDefinition* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_StructureDefinition* m_data;
};

#endif // UASTRUCTUREDEFINITIONDATATYPE_H

