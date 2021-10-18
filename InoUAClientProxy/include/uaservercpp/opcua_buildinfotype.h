/******************************************************************************
** opcua_buildinfotype.h
**
** Copyright (c) 2006-2018 Unified Automation GmbH. All rights reserved.
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
** Project: C++ OPC Server SDK information model for namespace http://opcfoundation.org/UA/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/

#ifndef __OPCUA_BUILDINFOTYPE_H__
#define __OPCUA_BUILDINFOTYPE_H__

#include "opcua_basedatavariabletype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class BaseDataVariableType;

/** Implements OPC UA Variables of the type BuildInfoType
 *
 *  **Variable members of the BuildInfoType:**
 *
 *  Browse Name      | DataType | TypeDefinition       | Modelling Rule | See Also
 *  -----------------|----------|----------------------|----------------|---------------------------------------------------
 *  BuildDate        | UtcTime  | BaseDataVariableType | Mandatory      | \ref getBuildDate, \ref setBuildDate
 *  BuildNumber      | String   | BaseDataVariableType | Mandatory      | \ref getBuildNumber, \ref setBuildNumber
 *  ManufacturerName | String   | BaseDataVariableType | Mandatory      | \ref getManufacturerName, \ref setManufacturerName
 *  ProductName      | String   | BaseDataVariableType | Mandatory      | \ref getProductName, \ref setProductName
 *  ProductUri       | String   | BaseDataVariableType | Mandatory      | \ref getProductUri, \ref setProductUri
 *  SoftwareVersion  | String   | BaseDataVariableType | Mandatory      | \ref getSoftwareVersion, \ref setSoftwareVersion
 *
 *  This complex variable type is used for information about the Server status.
 *
 *  Its data variables reflect its data type having the same semantic (see \ref
 *  UaBuildInfo "BuildInfo").
 *
 *  See also \ref Doc_OpcUa_BuildInfoType for a documentation of the complete Information Model.
 */
class SERVER_CORE_EXPORT BuildInfoType:
    public OpcUa::BaseDataVariableType
{
    UA_DISABLE_COPY(BuildInfoType);
protected:
    virtual ~BuildInfoType();
public:
    BuildInfoType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    BuildInfoType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    BuildInfoType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setBuildDate(const UaDateTime& BuildDate);
    virtual UaDateTime getBuildDate() const;

    virtual void setBuildNumber(const UaString& BuildNumber);
    virtual UaString getBuildNumber() const;

    virtual void setManufacturerName(const UaString& ManufacturerName);
    virtual UaString getManufacturerName() const;

    virtual void setProductName(const UaString& ProductName);
    virtual UaString getProductName() const;

    virtual void setProductUri(const UaString& ProductUri);
    virtual UaString getProductUri() const;

    virtual void setSoftwareVersion(const UaString& SoftwareVersion);
    virtual UaString getSoftwareVersion() const;

    virtual OpcUa::BaseDataVariableType* getBuildDateNode();
    virtual const OpcUa::BaseDataVariableType* getBuildDateNode() const;
    virtual OpcUa::BaseDataVariableType* getBuildNumberNode();
    virtual const OpcUa::BaseDataVariableType* getBuildNumberNode() const;
    virtual OpcUa::BaseDataVariableType* getManufacturerNameNode();
    virtual const OpcUa::BaseDataVariableType* getManufacturerNameNode() const;
    virtual OpcUa::BaseDataVariableType* getProductNameNode();
    virtual const OpcUa::BaseDataVariableType* getProductNameNode() const;
    virtual OpcUa::BaseDataVariableType* getProductUriNode();
    virtual const OpcUa::BaseDataVariableType* getProductUriNode() const;
    virtual OpcUa::BaseDataVariableType* getSoftwareVersionNode();
    virtual const OpcUa::BaseDataVariableType* getSoftwareVersionNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(BuildInfoType *pInstance);

protected:
    // Variable nodes
    // Variable BuildDate
    static OpcUa::BaseDataVariableType*  s_pBuildDate;
    OpcUa::BaseDataVariableType*  m_pBuildDate;
    // Variable BuildNumber
    static OpcUa::BaseDataVariableType*  s_pBuildNumber;
    OpcUa::BaseDataVariableType*  m_pBuildNumber;
    // Variable ManufacturerName
    static OpcUa::BaseDataVariableType*  s_pManufacturerName;
    OpcUa::BaseDataVariableType*  m_pManufacturerName;
    // Variable ProductName
    static OpcUa::BaseDataVariableType*  s_pProductName;
    OpcUa::BaseDataVariableType*  m_pProductName;
    // Variable ProductUri
    static OpcUa::BaseDataVariableType*  s_pProductUri;
    OpcUa::BaseDataVariableType*  m_pProductUri;
    // Variable SoftwareVersion
    static OpcUa::BaseDataVariableType*  s_pSoftwareVersion;
    OpcUa::BaseDataVariableType*  m_pSoftwareVersion;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_BUILDINFOTYPE_H__

