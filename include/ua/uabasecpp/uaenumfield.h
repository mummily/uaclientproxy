/******************************************************************************
** uaenumfield.h
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
** Portable UaEnumField class.
**
******************************************************************************/
#ifndef UAENUMFIELD_H
#define UAENUMFIELD_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "ualocalizedtext.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaEnumFieldPrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_EnumField.
 *
 *  This class encapsulates the native OpcUa_EnumField structure
 *  and handles memory allocation and cleanup for you.
 *  UaEnumField uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared EnumField it creates a copy for that (copy-on-write).
 *  So assigning another UaEnumField or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaEnumField
{
    UA_DECLARE_PRIVATE(UaEnumField)
public:
    UaEnumField();
    UaEnumField(const UaEnumField &other);
    UaEnumField(const OpcUa_EnumField &other);
    UaEnumField(
        OpcUa_Int64 value,
        const UaLocalizedText& displayName,
        const UaLocalizedText& description,
        const UaString& name
        );
    UaEnumField(const UaExtensionObject &extensionObject);
    UaEnumField(const OpcUa_ExtensionObject &extensionObject);
    UaEnumField(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaEnumField(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaEnumField();

    void clear();

    bool operator==(const UaEnumField &other) const;
    bool operator!=(const UaEnumField &other) const;

    UaEnumField& operator=(const UaEnumField &other);

    OpcUa_EnumField* copy() const;
    void copyTo(OpcUa_EnumField *pDst) const;

    static OpcUa_EnumField* clone(const OpcUa_EnumField& source);
    static void cloneTo(const OpcUa_EnumField& source, OpcUa_EnumField& copy);

    void attach(OpcUa_EnumField *pValue);
    OpcUa_EnumField* detach(OpcUa_EnumField* pDst);

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

    OpcUa_StatusCode setEnumField(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setEnumField(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setEnumField(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumField(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setEnumField(
        OpcUa_Int64 value,
        const UaLocalizedText& displayName,
        const UaLocalizedText& description,
        const UaString& name
        );

    OpcUa_Int64 getValue() const;
    UaLocalizedText getDisplayName() const;
    UaLocalizedText getDescription() const;
    UaString getName() const;

    void setValue(OpcUa_Int64 value);
    void setDisplayName(const UaLocalizedText& displayName);
    void setDescription(const UaLocalizedText& description);
    void setName(const UaString& name);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_EnumField.
 *
 *  This class encapsulates an array of the native OpcUa_EnumField structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaEnumField for information about the encapsulated structure.
 */
class UABASE_EXPORT UaEnumFields
{
public:
    UaEnumFields();
    UaEnumFields(const UaEnumFields &other);
    UaEnumFields(OpcUa_Int32 length, OpcUa_EnumField* data);
    virtual ~UaEnumFields();

    UaEnumFields& operator=(const UaEnumFields &other);
    const OpcUa_EnumField& operator[](OpcUa_UInt32 index) const;
    OpcUa_EnumField& operator[](OpcUa_UInt32 index);

    bool operator==(const UaEnumFields &other) const;
    bool operator!=(const UaEnumFields &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_EnumField* data);
    void attach(OpcUa_Int32 length, OpcUa_EnumField* data);
    OpcUa_EnumField* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_EnumField* rawData() const {return m_data;}
    inline OpcUa_EnumField* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setEnumFields(const UaVariant &variant);
    OpcUa_StatusCode setEnumFields(const OpcUa_Variant &variant);
    OpcUa_StatusCode setEnumFields(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumFields(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumFields(OpcUa_Int32 length, OpcUa_EnumField* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_EnumField* m_data;
};

#endif // UAENUMFIELD_H

