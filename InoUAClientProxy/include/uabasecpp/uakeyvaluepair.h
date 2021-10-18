/******************************************************************************
** uakeyvaluepair.h
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
** Portable UaKeyValuePair class.
**
******************************************************************************/
#ifndef UAKEYVALUEPAIR_H
#define UAKEYVALUEPAIR_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaqualifiedname.h"
#include "uavariant.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaDataValue;

class UABASE_EXPORT UaKeyValuePairPrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_KeyValuePair.
 *
 *  This class encapsulates the native OpcUa_KeyValuePair structure
 *  and handles memory allocation and cleanup for you.
 *  UaKeyValuePair uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared KeyValuePair it creates a copy for that (copy-on-write).
 *  So assigning another UaKeyValuePair or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaKeyValuePair
{
    UA_DECLARE_PRIVATE(UaKeyValuePair)
public:
    UaKeyValuePair();
    UaKeyValuePair(const UaKeyValuePair &other);
    UaKeyValuePair(const OpcUa_KeyValuePair &other);
    UaKeyValuePair(
        const UaQualifiedName& key,
        const UaVariant&value
        );
    UaKeyValuePair(const UaExtensionObject &extensionObject);
    UaKeyValuePair(const OpcUa_ExtensionObject &extensionObject);
    UaKeyValuePair(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaKeyValuePair(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaKeyValuePair();

    void clear();

    bool operator==(const UaKeyValuePair &other) const;
    bool operator!=(const UaKeyValuePair &other) const;

    UaKeyValuePair& operator=(const UaKeyValuePair &other);

    OpcUa_KeyValuePair* copy() const;
    void copyTo(OpcUa_KeyValuePair *pDst) const;

    static OpcUa_KeyValuePair* clone(const OpcUa_KeyValuePair& source);
    static void cloneTo(const OpcUa_KeyValuePair& source, OpcUa_KeyValuePair& copy);

    void attach(OpcUa_KeyValuePair *pValue);
    OpcUa_KeyValuePair* detach(OpcUa_KeyValuePair* pDst);

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

    OpcUa_StatusCode setKeyValuePair(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setKeyValuePair(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setKeyValuePair(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setKeyValuePair(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setKeyValuePair(
        const UaQualifiedName& key,
        const UaVariant&value
        );

    UaQualifiedName getKey() const;
    UaVariant getValue() const;

    void setKey(const UaQualifiedName& key);
    void setValue(const UaVariant&value);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_KeyValuePair.
 *
 *  This class encapsulates an array of the native OpcUa_KeyValuePair structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaKeyValuePair for information about the encapsulated structure.
 */
class UABASE_EXPORT UaKeyValuePairs
{
public:
    UaKeyValuePairs();
    UaKeyValuePairs(const UaKeyValuePairs &other);
    UaKeyValuePairs(OpcUa_Int32 length, OpcUa_KeyValuePair* data);
    virtual ~UaKeyValuePairs();

    UaKeyValuePairs& operator=(const UaKeyValuePairs &other);
    const OpcUa_KeyValuePair& operator[](OpcUa_UInt32 index) const;
    OpcUa_KeyValuePair& operator[](OpcUa_UInt32 index);

    bool operator==(const UaKeyValuePairs &other) const;
    bool operator!=(const UaKeyValuePairs &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_KeyValuePair* data);
    void attach(OpcUa_Int32 length, OpcUa_KeyValuePair* data);
    OpcUa_KeyValuePair* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_KeyValuePair* rawData() const {return m_data;}
    inline OpcUa_KeyValuePair* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setKeyValuePairs(const UaVariant &variant);
    OpcUa_StatusCode setKeyValuePairs(const OpcUa_Variant &variant);
    OpcUa_StatusCode setKeyValuePairs(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setKeyValuePairs(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setKeyValuePairs(OpcUa_Int32 length, OpcUa_KeyValuePair* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_KeyValuePair* m_data;
};

#endif // UAKEYVALUEPAIR_H

