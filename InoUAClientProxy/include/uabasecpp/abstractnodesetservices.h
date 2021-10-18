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
#ifndef ABSTRACTNODESETSERVICES_H
#define ABSTRACTNODESETSERVICES_H

#include <uabase.h>
#include <statuscode.h>
#include <uanodeid.h>

namespace UaBase
{

/** @brief Abstract base class defining an Interface for OPC UA Service Calls.
 *
 * This Interface is implemented by Nodeset to provide basic service capabilities on a
 * Nodeset.
 */
class UABASE_EXPORT AbstractNodesetServices
{
public:
    AbstractNodesetServices();
    virtual ~AbstractNodesetServices();

    /** @brief Browse OPC UA server Address Space with a single starting Node.
     *
     * The Browse Service is used by a client to navigate through the address space by passing
     * a starting Node and browse filters. The server returns the list of referenced nodes
     * matching the filter criteria.
     */
    virtual UaStatus browse(
            const UaNodeId&             nodeToBrowse,
            const OpcUa_BrowseDirection browseDirection,
            const UaNodeId&             referenceTypeId,
            const OpcUa_Boolean         includeSubtypes,
            const OpcUa_UInt32          nodeClassMask,
            const OpcUa_UInt32          resultMask,
            const OpcUa_UInt32          maxReferencesToReturn,
            UaByteString&               continuationPoint,
            UaReferenceDescriptions&    referenceDescriptions) const = 0;

    /** @brief Continue a previous Browse request.
     *
     * This method is only used to continue a Browse started with the browse method if not all
     * results could be returned by the browse or a following browseNext call.
     * The number of Nodes to return can be limited by the client in the Browse request or by
     * the Server during processing the Browse Service call.
     */
    virtual UaStatus browseNext(
            OpcUa_Boolean            releaseContinuationPoint,
            UaByteString&            continuationPoint,
            UaReferenceDescriptions& referenceDescriptions) const = 0;

    /** @brief Reads Attribute values synchronously from an OPC UA server.
     *
     * The Read Service is used to read one or more Attributes of one or more Nodes.
     * It also allows reading subsets or single elements of array values and to define
     * a valid age of values to be returned to reduce the need for device reads.
     * Like most other Services, the Read is optimized for bulk read operations and not
     * for reading single Attribute values. Typically all Node Attributes are readable.
     * For the Value Attribute, the Read rights are indicated by the AccessLevel and UserAccessLevel
     * Attribute of the Variable.
     */
    virtual UaStatus read(
            OpcUa_Double             maxAge,
            OpcUa_TimestampsToReturn timeStamps,
            const UaReadValueIds&    nodesToRead,
            UaDataValues&            values,
            UaDiagnosticInfos &diagnosticInfos) const = 0;

    /** @brief Writes variable values synchronously to an OPC UA server.
     *  Not implemented yet!
     */
    virtual UaStatus write(
        const UaWriteValues& nodesToWrite,
        UaStatusCodeArray&   results,
        UaDiagnosticInfos&   diagnosticInfos) ;// TODO: = 0;

protected:

    struct cPInternal {
        OpcUa_Int32 length;
        OpcUa_Int32 offset;
        OpcUa_Int32 refsPerCall;
        OpcUa_ReferenceDescription* references;
        ~cPInternal()
        {
            if (references)
            {
                for (OpcUa_Int32 i = 0; i < length; i++)
                {
                    OpcUa_ReferenceDescription_Clear(&references[i]);
                }
                OpcUa_Free(references);
                references = NULL;
            }
        }
    };
};

} // end namespace UaBase

#endif // ABSTRACTNODESETSERVICES_H
