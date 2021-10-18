/******************************************************************************
** uarolepermissiontype.h
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
** Portable UaRolePermissionType class.
**
******************************************************************************/
#ifndef UAROLEPERMISSIONTYPE_H
#define UAROLEPERMISSIONTYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uanodeid.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaRolePermissionTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_RolePermissionType.
 *
 *  This class encapsulates the native OpcUa_RolePermissionType structure
 *  and handles memory allocation and cleanup for you.
 *  UaRolePermissionType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared RolePermissionType it creates a copy for that (copy-on-write).
 *  So assigning another UaRolePermissionType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaRolePermissionType
{
    UA_DECLARE_PRIVATE(UaRolePermissionType)
public:
    UaRolePermissionType();
    UaRolePermissionType(const UaRolePermissionType &other);
    UaRolePermissionType(const OpcUa_RolePermissionType &other);
    UaRolePermissionType(
        const UaNodeId& roleId,
        OpcUa_PermissionType permissions
        );
    UaRolePermissionType(const UaExtensionObject &extensionObject);
    UaRolePermissionType(const OpcUa_ExtensionObject &extensionObject);
    UaRolePermissionType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaRolePermissionType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaRolePermissionType();

    void clear();

    bool operator==(const UaRolePermissionType &other) const;
    bool operator!=(const UaRolePermissionType &other) const;

    UaRolePermissionType& operator=(const UaRolePermissionType &other);

    OpcUa_RolePermissionType* copy() const;
    void copyTo(OpcUa_RolePermissionType *pDst) const;

    static OpcUa_RolePermissionType* clone(const OpcUa_RolePermissionType& source);
    static void cloneTo(const OpcUa_RolePermissionType& source, OpcUa_RolePermissionType& copy);

    void attach(OpcUa_RolePermissionType *pValue);
    OpcUa_RolePermissionType* detach(OpcUa_RolePermissionType* pDst);

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

    OpcUa_StatusCode setRolePermissionType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setRolePermissionType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setRolePermissionType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setRolePermissionType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setRolePermissionType(
        const UaNodeId& roleId,
        OpcUa_PermissionType permissions
        );

    UaNodeId getRoleId() const;
    OpcUa_PermissionType getPermissions() const;

    void setRoleId(const UaNodeId& roleId);
    void setPermissions(OpcUa_PermissionType permissions);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_RolePermissionType.
 *
 *  This class encapsulates an array of the native OpcUa_RolePermissionType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaRolePermissionType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaRolePermissionTypes
{
public:
    UaRolePermissionTypes();
    UaRolePermissionTypes(const UaRolePermissionTypes &other);
    UaRolePermissionTypes(OpcUa_Int32 length, OpcUa_RolePermissionType* data);
    virtual ~UaRolePermissionTypes();

    UaRolePermissionTypes& operator=(const UaRolePermissionTypes &other);
    const OpcUa_RolePermissionType& operator[](OpcUa_UInt32 index) const;
    OpcUa_RolePermissionType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaRolePermissionTypes &other) const;
    bool operator!=(const UaRolePermissionTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_RolePermissionType* data);
    void attach(OpcUa_Int32 length, OpcUa_RolePermissionType* data);
    OpcUa_RolePermissionType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_RolePermissionType* rawData() const {return m_data;}
    inline OpcUa_RolePermissionType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setRolePermissionTypes(const UaVariant &variant);
    OpcUa_StatusCode setRolePermissionTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setRolePermissionTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setRolePermissionTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setRolePermissionTypes(OpcUa_Int32 length, OpcUa_RolePermissionType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_RolePermissionType* m_data;
};

#endif // UAROLEPERMISSIONTYPE_H

