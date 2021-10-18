/******************************************************************************
** uaendpointtype.h
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
** Portable UaEndpointType class.
**
******************************************************************************/
#ifndef UAENDPOINTTYPE_H
#define UAENDPOINTTYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaEndpointTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_EndpointType.
 *
 *  This class encapsulates the native OpcUa_EndpointType structure
 *  and handles memory allocation and cleanup for you.
 *  UaEndpointType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared EndpointType it creates a copy for that (copy-on-write).
 *  So assigning another UaEndpointType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaEndpointType
{
    UA_DECLARE_PRIVATE(UaEndpointType)
public:
    UaEndpointType();
    UaEndpointType(const UaEndpointType &other);
    UaEndpointType(const OpcUa_EndpointType &other);
    UaEndpointType(
        const UaString& endpointUrl,
        OpcUa_MessageSecurityMode securityMode,
        const UaString& securityPolicyUri,
        const UaString& transportProfileUri
        );
    UaEndpointType(const UaExtensionObject &extensionObject);
    UaEndpointType(const OpcUa_ExtensionObject &extensionObject);
    UaEndpointType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaEndpointType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaEndpointType();

    void clear();

    bool operator==(const UaEndpointType &other) const;
    bool operator!=(const UaEndpointType &other) const;

    UaEndpointType& operator=(const UaEndpointType &other);

    OpcUa_EndpointType* copy() const;
    void copyTo(OpcUa_EndpointType *pDst) const;

    static OpcUa_EndpointType* clone(const OpcUa_EndpointType& source);
    static void cloneTo(const OpcUa_EndpointType& source, OpcUa_EndpointType& copy);

    void attach(OpcUa_EndpointType *pValue);
    OpcUa_EndpointType* detach(OpcUa_EndpointType* pDst);

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

    OpcUa_StatusCode setEndpointType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setEndpointType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setEndpointType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEndpointType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setEndpointType(
        const UaString& endpointUrl,
        OpcUa_MessageSecurityMode securityMode,
        const UaString& securityPolicyUri,
        const UaString& transportProfileUri
        );

    UaString getEndpointUrl() const;
    OpcUa_MessageSecurityMode getSecurityMode() const;
    UaString getSecurityPolicyUri() const;
    UaString getTransportProfileUri() const;

    void setEndpointUrl(const UaString& endpointUrl);
    void setSecurityMode(OpcUa_MessageSecurityMode securityMode);
    void setSecurityPolicyUri(const UaString& securityPolicyUri);
    void setTransportProfileUri(const UaString& transportProfileUri);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_EndpointType.
 *
 *  This class encapsulates an array of the native OpcUa_EndpointType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaEndpointType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaEndpointTypes
{
public:
    UaEndpointTypes();
    UaEndpointTypes(const UaEndpointTypes &other);
    UaEndpointTypes(OpcUa_Int32 length, OpcUa_EndpointType* data);
    virtual ~UaEndpointTypes();

    UaEndpointTypes& operator=(const UaEndpointTypes &other);
    const OpcUa_EndpointType& operator[](OpcUa_UInt32 index) const;
    OpcUa_EndpointType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaEndpointTypes &other) const;
    bool operator!=(const UaEndpointTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_EndpointType* data);
    void attach(OpcUa_Int32 length, OpcUa_EndpointType* data);
    OpcUa_EndpointType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_EndpointType* rawData() const {return m_data;}
    inline OpcUa_EndpointType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setEndpointTypes(const UaVariant &variant);
    OpcUa_StatusCode setEndpointTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setEndpointTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEndpointTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEndpointTypes(OpcUa_Int32 length, OpcUa_EndpointType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_EndpointType* m_data;
};

#endif // UAENDPOINTTYPE_H

