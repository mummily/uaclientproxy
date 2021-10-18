/******************************************************************************
** uastructurefielddatatype.h
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
** Portable UaStructureFieldDataType class.
**
******************************************************************************/
#ifndef UASTRUCTUREFIELDDATATYPE_H
#define UASTRUCTUREFIELDDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "ualocalizedtext.h"
#include "uanodeid.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaStructureFieldDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_StructureField.
 *
 *  This class encapsulates the native OpcUa_StructureField structure
 *  and handles memory allocation and cleanup for you.
 *  UaStructureFieldDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared StructureFieldDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaStructureFieldDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaStructureFieldDataType
{
    UA_DECLARE_PRIVATE(UaStructureFieldDataType)
public:
    UaStructureFieldDataType();
    UaStructureFieldDataType(const UaStructureFieldDataType &other);
    UaStructureFieldDataType(const OpcUa_StructureField &other);
    UaStructureFieldDataType(
        const UaString& name,
        const UaLocalizedText& description,
        const UaNodeId& dataType,
        OpcUa_Int32 valueRank,
        const UaUInt32Array &arrayDimensions,
        OpcUa_UInt32 maxStringLength,
        OpcUa_Boolean isOptional
        );
    UaStructureFieldDataType(const UaExtensionObject &extensionObject);
    UaStructureFieldDataType(const OpcUa_ExtensionObject &extensionObject);
    UaStructureFieldDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaStructureFieldDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaStructureFieldDataType();

    void clear();

    bool operator==(const UaStructureFieldDataType &other) const;
    bool operator!=(const UaStructureFieldDataType &other) const;

    UaStructureFieldDataType& operator=(const UaStructureFieldDataType &other);

    OpcUa_StructureField* copy() const;
    void copyTo(OpcUa_StructureField *pDst) const;

    static OpcUa_StructureField* clone(const OpcUa_StructureField& source);
    static void cloneTo(const OpcUa_StructureField& source, OpcUa_StructureField& copy);

    void attach(OpcUa_StructureField *pValue);
    OpcUa_StructureField* detach(OpcUa_StructureField* pDst);

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

    OpcUa_StatusCode setStructureField(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setStructureField(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setStructureField(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setStructureField(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setStructureField(
        const UaString& name,
        const UaLocalizedText& description,
        const UaNodeId& dataType,
        OpcUa_Int32 valueRank,
        const UaUInt32Array &arrayDimensions,
        OpcUa_UInt32 maxStringLength,
        OpcUa_Boolean isOptional
        );

    UaString getName() const;
    UaLocalizedText getDescription() const;
    UaNodeId getDataType() const;
    OpcUa_Int32 getValueRank() const;
    void getArrayDimensions(UaUInt32Array& arrayDimensions) const;
    OpcUa_UInt32 getMaxStringLength() const;
    OpcUa_Boolean getIsOptional() const;

    void setName(const UaString& name);
    void setDescription(const UaLocalizedText& description);
    void setDataType(const UaNodeId& dataType);
    void setValueRank(OpcUa_Int32 valueRank);
    void setArrayDimensions(const UaUInt32Array &arrayDimensions);
    void setMaxStringLength(OpcUa_UInt32 maxStringLength);
    void setIsOptional(OpcUa_Boolean isOptional);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_StructureField.
 *
 *  This class encapsulates an array of the native OpcUa_StructureField structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaStructureFieldDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaStructureFieldDataTypes
{
public:
    UaStructureFieldDataTypes();
    UaStructureFieldDataTypes(const UaStructureFieldDataTypes &other);
    UaStructureFieldDataTypes(OpcUa_Int32 length, OpcUa_StructureField* data);
    virtual ~UaStructureFieldDataTypes();

    UaStructureFieldDataTypes& operator=(const UaStructureFieldDataTypes &other);
    const OpcUa_StructureField& operator[](OpcUa_UInt32 index) const;
    OpcUa_StructureField& operator[](OpcUa_UInt32 index);

    bool operator==(const UaStructureFieldDataTypes &other) const;
    bool operator!=(const UaStructureFieldDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_StructureField* data);
    void attach(OpcUa_Int32 length, OpcUa_StructureField* data);
    OpcUa_StructureField* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_StructureField* rawData() const {return m_data;}
    inline OpcUa_StructureField* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setStructureFields(const UaVariant &variant);
    OpcUa_StatusCode setStructureFields(const OpcUa_Variant &variant);
    OpcUa_StatusCode setStructureFields(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setStructureFields(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setStructureFields(OpcUa_Int32 length, OpcUa_StructureField* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_StructureField* m_data;
};

#endif // UASTRUCTUREFIELDDATATYPE_H

