/*********************************************************************
Copyright 2013 KDIS
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

For Further Information Please Contact me at
Karljj1@yahoo.com
http://p.sf.net/kdis/UserGuide
*********************************************************************/

/********************************************************************
    class:      Minefield_Response_NACK_PDU
    DIS:        (6) 1278.1a - 1998
    created:    25/06/2010
    author:     Karl Jones

    purpose:    Provides the means by which a simulation shall request a minefield
                simulation to retransmit Minefield Data PDUs not received in response
                to a query when operating in QRP mode.
    size:       208 bits / 26 octets  - Min size
*********************************************************************/

#pragma once

#include "./Minefield_Header.h"
#include "./../../DataTypes/EntityType.h"
#include <vector>

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::EntityType;
using std::vector;

class KDIS_EXPORT Minefield_Response_NACK_PDU : public Minefield_Header
{
protected:

    EntityIdentifier m_ReqID;

    KUINT8 m_ui8ReqID;

    KUINT8 m_ui8NumMisPdus;

    vector<KUINT8> m_vSeqNums;

public:

    static const KUINT16 MINEFIELD_RESPONSE_NACK_SIZE = 26; // Min size

    Minefield_Response_NACK_PDU( void );

    Minefield_Response_NACK_PDU( const EntityIdentifier & MinefieldID, const EntityIdentifier & RequestingSimulationID,
                                 KUINT8 ReqID );

    Minefield_Response_NACK_PDU( const EntityIdentifier & MinefieldID, const EntityIdentifier & RequestingSimulationID,
                                 KUINT8 ReqID, const vector<KUINT8> & MissingSeqNums );

    Minefield_Response_NACK_PDU( KDataStream & stream ) throw( KException );

    virtual ~Minefield_Response_NACK_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::Minefield_Response_NACK_PDU::SetRequestingSimulationID
    //              KDIS::PDU::Minefield_Response_NACK_PDU::GetRequestingSimulationID
    // Description: Identifies the simulation that generated the query and is requesting
    //              retransmission of information from the minefield simulation.
    // Parameter:   const EntityIdentifier & ID
    //************************************
    void SetRequestingSimulationID( const EntityIdentifier & ID );
    const EntityIdentifier & GetRequestingSimulationID() const;
    EntityIdentifier & GetRequestingSimulationID();

    //************************************
    // FullName:    KDIS::PDU::Minefield_Response_NACK_PDU::SetRequestID
    //              KDIS::PDU::Minefield_Response_NACK_PDU::GetRequestID
    // Description: Identifies the minefield query request.
    // Parameter:   KUINT8 ID
    //************************************
    void SetRequestID( KUINT8 ID );
    KUINT8 GetRequestID() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Response_NACK_PDU::GetNumberMissingPDUs
    // Description: Identifies the number of PDUs that were not received by
    //              the requesting simulation in response to a minefield query request.
    //              This value is derived from the Minefield Data PDUs that were
    //              received in response to the minefield query request.
    //************************************
    KUINT8 GetNumberMissingPDUs() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Response_NACK_PDU::GetNumberMissingPDUs
    //              KDIS::PDU::Minefield_Response_NACK_PDU::SetMissingPDUSequenceNumbers
    //              KDIS::PDU::Minefield_Response_NACK_PDU::GetMissingPDUSequenceNumbers
    //              KDIS::PDU::Minefield_Response_NACK_PDU::ClearMissingPDUSequenceNumbers
    // Description: The sequence number(s) of the missing PDU(s).
    //              These values are derived from the Minefield Data PDUs that were
    //              received in response to the minefield query request.
    // Parameter:   KUINT8 N, const vector<KUINT8> & N
    //************************************
    void AddMissingPDUSequenceNumber( KUINT8 N );
    void SetMissingPDUSequenceNumbers( const vector<KUINT8> & N );
    const vector<KUINT8> & GetMissingPDUSequenceNumbers() const;
    void ClearMissingPDUSequenceNumbers();

    //************************************
    // FullName:    KDIS::PDU::Minefield_Response_NACK_PDU::GetAsString
    // Description: Returns a string representation of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Response_NACK_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Minefield_Response_NACK_PDU::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Minefield_Response_NACK_PDU & Value ) const;
    KBOOL operator != ( const Minefield_Response_NACK_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS
