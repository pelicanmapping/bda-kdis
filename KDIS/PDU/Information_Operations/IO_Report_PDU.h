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
    class:      IO_Report_PDU
    DIS:        (7) 1278.1-200x
    created:    20/01/2011
    author:     Karl Jones

    purpose:    The information operations status of an entity shall be
                conveyed using the Information Operations Report PDU.
                This includes reporting the status of any entities
                and their associated equipment that are susceptible to
                an IO attack.
    Size:       320 bits / 40 octets - min size not including standard variables
*********************************************************************/

#pragma once

#include "./IO_Header.h"

// Standard Variable Records
#include "./../../DataTypes/IOCommunicationsNode.h"
#include "./../../DataTypes/IOEffect.h"

namespace KDIS {
namespace PDU {

using KDIS::DATA_TYPE::EntityIdentifier;
using KDIS::DATA_TYPE::ENUMS::IOReportType;
using KDIS::DATA_TYPE::StdVarPtr;

class KDIS_EXPORT IO_Report_PDU : public IO_Header
{
protected:

    KUINT16 m_ui16SimSrc;

    KUINT8 m_ui8RptTyp;

    EntityIdentifier m_AtkEntityID;

    EntityIdentifier m_TgtEntityID;

    KUINT32 m_ui32Padding; // 2 * KUINT16 padding in 1278.1-200x standard.

    KUINT16 m_ui16NumStdVarRec;

    vector<StdVarPtr> m_vStdVarRecs;

public:

    static const KUINT16 IO_REPORT_PDU_SIZE = 40;

    IO_Report_PDU( void );

    IO_Report_PDU( const EntityIdentifier & OrigID, KUINT16 SimSrc, IOReportType RT,
                   const EntityIdentifier & AtkID, const EntityIdentifier & TgtID );

    IO_Report_PDU( KDataStream & stream ) throw( KException );

    virtual ~IO_Report_PDU( void );

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::SetSimulationSource
    //              KDIS::PDU::IO_Report_PDU::GetSimulationSource
    // Description: Identifies the name of the simulation model issuing this PDU.
    //              0       No statement.
    //              1-200   Reserved for future Io simulation sources.
    //              201-255 Reserved for United States IO Simulation Sources �
    //                      See applicable agreement or the organizers of the event
    //                      (training, exercise, etc) in which information operations
    //                      is included.
    // Parameter:   KUINT16 SS
    //************************************
    void SetSimulationSource( KUINT16 SS );
    KUINT16 GetSimulationSource() const;

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::SetReportType
    //              KDIS::PDU::IO_Report_PDU::GetReportType
    // Description: The type of report this PDU represents.
    // Parameter:   IOReportType RT
    //************************************
    void SetReportType( IOReportType RT );
    IOReportType GetReportType() const;

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::SetAttackerEntityID
    //              KDIS::PDU::IO_Report_PDU::GetAttackerEntityID
    // Description: Identifies the IO Attacker Entity ID.
    // Parameter:   const EntityIdentifier & ID
    //************************************
    void SetAttackerEntityID( const EntityIdentifier & ID );
    const EntityIdentifier & GetAttackerEntityID() const;
    EntityIdentifier & GetAttackerEntityID();

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::SetPrimaryTargetEntityID
    //              KDIS::PDU::IO_Report_PDU::GetPrimaryTargetEntityID
    // Description: Identifies the IO Primary Target Entity ID.
    // Parameter:   const EntityIdentifier & ID
    //************************************
    void SetPrimaryTargetEntityID( const EntityIdentifier & ID );
    const EntityIdentifier & GetPrimaryTargetEntityID() const;
    EntityIdentifier & GetPrimaryTargetEntityID();

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::GetNumberOfIORecords
    // Description: Indicates the number of IO standard variable records included.
    //************************************
    KUINT16 GetNumberOfIORecords() const;

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::AddStandardVariableRecord
    //              KDIS::PDU::IO_Report_PDU::SetStandardVariableRecords
    //              KDIS::PDU::IO_Report_PDU::GetStandardVariableRecords
    //              KDIS::PDU::IO_Report_PDU::ClearStandardVariableRecords
    // Description: The following Standard Records currently exist:
    //              -   IOCommunicationsNode
    //              -   IOEffect
    // Parameter:   StdVarPtr SVR, const vector<StdVarPtr> & SVR
    //************************************
    void AddStandardVariableRecord( StdVarPtr SVR );
    void SetStandardVariableRecords( const vector<StdVarPtr> & SVR );
    const vector<StdVarPtr> & GetStandardVariableRecords() const;
    void ClearStandardVariableRecords();

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::GetAsString
    // Description: Returns a string representation of the PDU.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::PDU::IO_Report_PDU::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const IO_Report_PDU & Value ) const;
    KBOOL operator != ( const IO_Report_PDU & Value ) const;
};

}; // END namespace PDU
}; // END namespace KDIS
