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

/*!
    \file ticket.h
    \brief Broker ticket management header file.
*/

#ifndef _REMOTE_CMPI_TICKET_H
#define _REMOTE_CMPI_TICKET_H

typedef struct comm_ticket comm_ticket;

#ifndef CMPI_VER_100
# define CMPI_VER_100
#endif

#ifndef CONST
# ifdef CMPI_VER_100
#  define CONST const
# else
#  define CONST
# endif
#endif

#include <Pegasus/Provider/CMPI/cmpidt.h>

//! Communication ticket given to remote providers to grant them up-calls.
/*!
    This ticket is being generated by the proxy provider and passed along with
    MI and MB calls to remote providers. This way MB calls can be verified and
    associated to the proper broker handle.
*/
struct comm_ticket
{
    unsigned long id;   /*!< ticket id */
    CONST CMPIBroker * broker;  /*!< originating broker */
    struct comm_ticket * next; /*! next element pointer */
};


/****************************************************************************/

PEGASUS_EXPORT CONST CMPIBroker * verify_ticket ( const comm_ticket * ticket );
comm_ticket generate_ticket ( CONST CMPIBroker * broker );
int revoke_ticket ( comm_ticket * ticket );
int compare_ticket ( const comm_ticket *, const comm_ticket * );
void cleanup_ticket ();

#endif

/****************************************************************************/

/*** Local Variables:  ***/
/*** mode: C           ***/
/*** c-basic-offset: 8 ***/
/*** End:              ***/
