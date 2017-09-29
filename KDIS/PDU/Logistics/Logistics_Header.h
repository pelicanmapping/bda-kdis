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
    class:      Logistics_Header
    DIS:        (5) 1278.1 - 1995
    created:    2008/09/17
    author:     Karl Jones

    purpose:    Header for all Logistics PDU's
    Size:       192 bits / 24 octets
*********************************************************************/

#pragma once

#include "./../Header.h"
#include "./../../DataTypes/EntityIdentifier.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;

class KDIS_EXPORT Logistics_Header : public Header
{
protected:

    EntityIdentifier m_ReceivingEntity;

    EntityIdentifier m_SupplyingEntity;

public:

    static const KUINT16 LOGISTICS_HEADER_SIZE = 24;

    Logistics_Header( void );

    Logistics_Header( const EntityIdentifier & ReceivingEntityID, const EntityIdentifier & SupplyingEntityID );

    virtual ~Logistics_Header( void );

    //************************************
    // FullName:    KDIS::PDU::Logistics_Header::SetReceivingEntity
    //              KDIS::PDU::Logistics_Header::GetReceivingEntity
    // Description: Entity Receiving the supplies/repairs
    // Parameter:   const EntityIdentifier & EI
    //************************************
    void SetReceivingEntity( const EntityIdentifier & EI );
    const EntityIdentifier & GetReceivingEntity() const;
    EntityIdentifier & GetReceivingEntity();

    //************************************
    // FullName:    KDIS::PDU::Logistics_Header::SetSupplyingEntity
    //              KDIS::PDU::Logistics_Header::GetSupplyingEntity
    // Description: Entity providing the supplies/repairs
    // Parameter:   const EntityIdentifier & EI, void
    //************************************
    void SetSupplyingEntity( const EntityIdentifier & EI );
    const EntityIdentifier & GetSupplyingEntity() const;
    EntityIdentifier & GetSupplyingEntity();

    //************************************
    // FullName:    KDIS::PDU::Logistics_Header::GetAsString
    // Description: Returns a string representation
    //              of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Logistics_Header::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Logistics_Header::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Logistics_Header & Value ) const;
    KBOOL operator != ( const Logistics_Header & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS
