//%LICENSE////////////////////////////////////////////////////////////////
//
// Licensed to The Open Group (TOG) under one or more contributor license
// agreements.  Refer to the OpenPegasusNOTICE.txt file distributed with
// this work for additional information regarding copyright ownership.
// Each contributor licenses this file to you under the OpenPegasus Open
// Source License; you may not use this file except in compliance with the
// License.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////
//
//%/////////////////////////////////////////////////////////////////////////////

#ifndef Pegasus_QuerySupportRouter_h
#define Pegasus_QuerySupportRouter_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/String.h>

#include <Pegasus/Server/CIMOperationRequestDispatcher.h>

PEGASUS_NAMESPACE_BEGIN

/**
    This class is the basis for encapsulating Query support such that
    CIMOperationRequestDispatcher.cpp is not to be changed for adding
    new/additional types of query support.

    The router provides routing of two functions
        - routeHandleExecQueryRequest
        - routeApplyQueryToEnumeration

    where the corresponding functions:
        - handleExecQueryRequest
        - applyQueryToEnumeration

    are specific the the query language.

    New types of query support need to subclass
    CIMOperationRequestDispatcher as can be seen in
    WQLCIMOperatioRequestDispatcher.

    The QuerySupportRouter.cpp must be extended to recognize
    the new  query language identifier and route the requests to
    the appropriate query language processor. The new query
    language processor has to be added to the pegserver library.

    In addition, ProviderManager2/QueryExpressionFactory.h has to be
    extended similarly.
*/

// Define a typedef for the pointer to applyQueryToEnumeration function
typedef void (*applyQueryFunctionPtr)(
                   CIMResponseMessage* msg,
                   QueryExpressionRep* query);

class QuerySupportRouter
{
public:
    /*  Handle the ExecQuery request by handing it off to the
        correct handler for the defined query language. The handler validates
        the request and processes it either by doing an enumeration and
        filtering the result or handing it to the provider if the provider has
        query processing capabilities.
        @param opThis
        @param msg CIMExecQueryRequestMessage to be processed
        @return true if the query language is supported.
        @exception Exceptions may be generated by the individual handlers

    */
    static Boolean routeHandleExecQueryRequest(
        CIMOperationRequestDispatcher* opThis,
        CIMExecQueryRequestMessage* msg);

    /** get pointer to  the correct applyQueryToEnumeration function
     *  @param opThis
     *  @param query Query ExpressionRep containing query. Used to
     *  access query language
     *  @return applyQueryToEnumerationPtr pointer to function
    */
    static applyQueryFunctionPtr getFunctPtr(
       CIMOperationRequestDispatcher* opThis,
       QueryExpressionRep* query);
};


PEGASUS_NAMESPACE_END

#endif
