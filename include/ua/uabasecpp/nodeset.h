/******************************************************************************
** Copyright (c) 2016-2018 Unified Automation GmbH. All rights reserved.
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
******************************************************************************/
#ifndef _NODEMODEL_H_
#define _NODEMODEL_H_

#include <map>
#include <uanodeid.h>
#include <basenodes.h>
#include <abstractnodesetservices.h>

namespace UaBase
{

/**  @brief Container Class for a Nodeset of OPC UA Nodes.
 *
 * This class is used to store an imported OPC UA Addressspace (or parts of it)
 * and provides a STL like interface to work with the data.
 * The internal representation for data storage is a std::map of UaBase::BaseNodes
 * but can change in future revisions. Therefore the public STL interface (iterators and standard
 * operations like e.g. empty()) is provided.
 *
 * This class implements the AbstractNodesetServices Interface which provides a more UA like way to
 * interact with a Nodeset. This implementation is used to implement, for example the
 * UaAbstractDictionaryReader interface in UaBase::AbstractNodesetExport .
 */
class UABASE_EXPORT Nodeset :
    public AbstractNodesetServices
{
public:
    Nodeset();
    ~Nodeset();

    // STL Style Interface
    // Typenames
    typedef std::map<UaNodeId, BaseNode*>::const_iterator const_iterator;
    typedef std::map<UaNodeId, BaseNode*>::iterator iterator;
    typedef std::map<UaNodeId, BaseNode*>::size_type size_type;
    typedef UaNodeId key_type;
    typedef std::pair<key_type, BaseNode*> value_type;

    //Iterators
    inline const_iterator begin() const { return(m_nodes.begin()); }
    inline iterator begin() { return(m_nodes.begin()); }
    inline const_iterator end() const { return(m_nodes.end()); }
    inline iterator end() { return(m_nodes.end()); }

    //Basic STL functionality
    inline size_type count(const key_type& key) const { return m_nodes.count(key); }
    inline size_type size() const { return m_nodes.size(); }
    inline void insert (iterator first, iterator last) { return m_nodes.insert(first,last); }
    inline const_iterator find(const key_type& key) const { return m_nodes.find(key); }
    inline bool empty() const { return m_nodes.empty(); }
    inline void clear() {
                            iterator it = begin();
                            while ( it != end() )
                            {
                                    delete it->second;
                                    it++;
                            }
                            m_nodes.clear();
                        }
    //Operators
    inline bool
    operator==(const Nodeset& y)
        { return m_nodes == y.m_nodes; }
    BaseNode*& operator[](const UaNodeId &nodeId) { return m_nodes[nodeId]; }

    BaseNode* newNode(UaNodeId nodeId, OpcUa_NodeClass nodeClass);
    bool deleteNode(UaNodeId nodeId);
    BaseNodeFactory* getNodeFactory() const { return m_baseNodeFactory; }

    void setNamespaces(const UaStringArray& namespaceUris);
    const UaStringArray& getNamespaces() const;
    OpcUa_UInt32 numberOfNamespaces() const;
    UaUInt16Array getNamespaceIndices(const UaStringArray& nsUris) const;
    const std::map<OpcUa_UInt16, OpcUa_UInt16> getNamespaceMapping() const;
    bool setNamespaceMapping(const std::map<OpcUa_UInt16, OpcUa_UInt16> &newMapping);
    bool remapNamespaces();
    bool remapNamespaces(const std::map<OpcUa_UInt16, OpcUa_UInt16>& mapping);

    //Implementation of the AbstractNodesetServices Interface
    virtual UaStatus browse(
            const UaNodeId&             nodeToBrowse,
            const OpcUa_BrowseDirection browseDirection,
            const UaNodeId&             referenceTypeId,
            const OpcUa_Boolean         includeSubtypes,
            const OpcUa_UInt32          nodeClassMask,
            const OpcUa_UInt32          resultMask,
            const OpcUa_UInt32          maxReferencesToReturn,
            UaByteString&               continuationPoint,
            UaReferenceDescriptions&    referenceDescriptions) const;

    virtual UaStatus browseNext(
            OpcUa_Boolean            releaseContinuationPoint,
            UaByteString&            continuationPoint,
            UaReferenceDescriptions& referenceDescriptions) const;

    virtual UaStatus read(OpcUa_Double             maxAge,
            OpcUa_TimestampsToReturn timeStamps,
            const UaReadValueIds&    nodesToRead,
            UaDataValues&            values,
            UaDiagnosticInfos &diagnosticInfos) const;

private:
    //non public STL Interface to restrict access to implementation internals

    inline std::pair<iterator, bool> insert(const value_type& node) { return m_nodes.insert(node); }
    inline size_type erase(const key_type& key) { return m_nodes.erase(key); }

    //helpers for offline browsing
    bool checkRefType(UaNodeId typeId, const UaNodeId& selectId, OpcUa_Boolean includeSubtype) const;
    bool checkRefTypeRec(UaNodeId typeId, const UaNodeId& selectId) const;
    bool checkRefTypeNS0(const OpcUa_UInt32 typeId, const OpcUa_UInt32 selectId) const;

    std::map<UaNodeId, BaseNode*> m_nodes;
    UaStringArray m_namespaces;
    BaseNodeFactory* m_baseNodeFactory;
    std::map<OpcUa_UInt16, OpcUa_UInt16> m_nsmap;

};

} // end namespace UaBase

#endif //_NODEMODEL_H_
