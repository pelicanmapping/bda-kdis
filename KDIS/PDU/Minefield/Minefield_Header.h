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
    class:      Minefield_Header
    DIS:        (6) 1278.1a - 1998
    created:    13/04/2010
    author:     Karl Jones

    purpose:    Contains common attributes for all minefield PDU.

    size:       144 bits / 18 octets
*********************************************************************/

#pragma once

#include "./../Header.h"
#include "./../../DataTypes/EntityIdentifier.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;

class KDIS_EXPORT Minefield_Header : public Header
{
protected:

    EntityIdentifier m_MinefieldID;

public:

    static const KUINT16 MINEFIELD_HEADER_SIZE = 18;

    Minefield_Header( void );

    Minefield_Header( KDataStream & stream ) throw( KException );

    virtual ~Minefield_Header( void );

    //************************************
    // FullName:    KDIS::PDU::Minefield_Header::SetMinefieldID
    //              KDIS::PDU::Minefield_Header::GetMinefieldID
    // Description: The Minefield Identifier (Minefield ID) does not represent an entity but
    //              rather an aggregation of mine entities for the purpose of conserving bandwidth.
    // Parameter:   const EntityIdentifier & ID, void
    //************************************
    void SetMinefieldID( const EntityIdentifier & ID );
    const EntityIdentifier & GetMinefieldID() const;
    EntityIdentifier & GetMinefieldID();

    //************************************
    // FullName:    KDIS::PDU::Minefield_Header::GetAsString
    // Description: Returns a string representation of the PDU
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::Minefield_Header::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::Minefield_Header::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const Minefield_Header & Value ) const;
    KBOOL operator != ( const Minefield_Header & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS
