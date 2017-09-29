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

#include "./Articulated_Parts_PDU.h"

//////////////////////////////////////////////////////////////////////////

using namespace KDIS;
using namespace PDU;
using namespace DATA_TYPE;
using namespace std;
using namespace ENUMS;
using namespace UTILS;

//////////////////////////////////////////////////////////////////////////
// public:
//////////////////////////////////////////////////////////////////////////

Articulated_Parts_PDU::Articulated_Parts_PDU( void ) :
    m_ui8NumOfArticulationParams( 0 )
{
    m_ui8PDUType = ArticulatedParts_PDU_Type;
    m_ui16PDULength = ARTICULATED_PARTS_PDU_SIZE;
}

//////////////////////////////////////////////////////////////////////////

Articulated_Parts_PDU::Articulated_Parts_PDU( const LE_EntityIdentifier & ID ) :
    m_ui8NumOfArticulationParams( 0 )
{
    m_EntID = ID;
    m_ui8PDUType = ArticulatedParts_PDU_Type;
    m_ui16PDULength = ARTICULATED_PARTS_PDU_SIZE;
}

//////////////////////////////////////////////////////////////////////////

Articulated_Parts_PDU::Articulated_Parts_PDU( KDataStream & stream ) throw( KException )
{
    try
    {
        Decode( stream );
    }
    catch ( KException & e )
    {
        throw e;
    }
}

//////////////////////////////////////////////////////////////////////////

Articulated_Parts_PDU::~Articulated_Parts_PDU( void )
{
}

//////////////////////////////////////////////////////////////////////////

KUINT8 Articulated_Parts_PDU::GetNumberOfArticulationParams() const
{
    return m_ui8NumOfArticulationParams;
}

//////////////////////////////////////////////////////////////////////////

void Articulated_Parts_PDU::AddArticulationParameter( const ArticulationParameters & AP )
{
    m_vArticulationParameters.push_back( AP );
    ++m_ui8NumOfArticulationParams;
    m_ui16PDULength += ArticulationParameters::ARTICULATION_PARAMETERS_SIZE;
}

//////////////////////////////////////////////////////////////////////////

void Articulated_Parts_PDU::SetArticulationParameters( const vector<ArticulationParameters> & AP )
{
    m_vArticulationParameters = AP;
    m_ui8NumOfArticulationParams = m_vArticulationParameters.size();
    m_ui16PDULength = ARTICULATED_PARTS_PDU_SIZE + ( m_ui8NumOfArticulationParams * ArticulationParameters::ARTICULATION_PARAMETERS_SIZE );
}

//////////////////////////////////////////////////////////////////////////

void Articulated_Parts_PDU::ClearArticulationParameters()
{
    m_vArticulationParameters.clear();
    m_ui8NumOfArticulationParams = 0;
    m_ui16PDULength = ARTICULATED_PARTS_PDU_SIZE;
}

//////////////////////////////////////////////////////////////////////////

KString Articulated_Parts_PDU::GetAsString() const
{
    KStringStream ss;

    ss << LE_Header::GetAsString()
       << "-Articulated Parts PDU-\n"
       << "Number Of Art Parts: " << ( KUINT16 )m_ui8NumOfArticulationParams << "\n";

    // Articulated parts
    vector<ArticulationParameters>::const_iterator citr = m_vArticulationParameters.begin();
    vector<ArticulationParameters>::const_iterator citrEnd = m_vArticulationParameters.end();
    for( ; citr != citrEnd; ++ citr )
    {
        ss << citr->GetAsString();
    }

    return ss.str();
}

//////////////////////////////////////////////////////////////////////////

void Articulated_Parts_PDU::Decode( KDataStream & stream ) throw( KException )
{
    if( stream.GetBufferSize() < ARTICULATED_PARTS_PDU_SIZE )throw KException( __FUNCTION__, NOT_ENOUGH_DATA_IN_BUFFER );

    m_vArticulationParameters.clear();

    LE_Header::Decode( stream );

    stream >> m_ui8NumOfArticulationParams;

    for( KUINT8 i = 0; i < m_ui8NumOfArticulationParams; ++i )
    {
        m_vArticulationParameters.push_back( ArticulationParameters( stream ) );
    }
}

//////////////////////////////////////////////////////////////////////////

KDataStream Articulated_Parts_PDU::Encode() const
{
    KDataStream stream;

    Articulated_Parts_PDU::Encode( stream );

    return stream;
}

//////////////////////////////////////////////////////////////////////////

void Articulated_Parts_PDU::Encode( KDataStream & stream ) const
{
    LE_Header::Encode( stream );

    stream << m_ui8NumOfArticulationParams;

    // Add the articulated parts
    vector<ArticulationParameters>::const_iterator citr = m_vArticulationParameters.begin();
    vector<ArticulationParameters>::const_iterator citrEnd = m_vArticulationParameters.end();
    for( ; citr != citrEnd; ++ citr )
    {
        citr->Encode( stream );
    }
}

//////////////////////////////////////////////////////////////////////////

KBOOL Articulated_Parts_PDU::operator == ( const Articulated_Parts_PDU & Value ) const
{
    if( LE_Header::operator          != ( Value ) )                         return false;
    if( m_ui8NumOfArticulationParams != Value.m_ui8NumOfArticulationParams )return false;
    if( m_vArticulationParameters    != Value.m_vArticulationParameters )   return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////

KBOOL Articulated_Parts_PDU::operator != ( const Articulated_Parts_PDU & Value ) const
{
    return !( *this == Value );
}

//////////////////////////////////////////////////////////////////////////


