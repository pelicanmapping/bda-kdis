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
    class:      ArticulationParameters
    created:    24/09/2008
    author:     Karl Jones

    purpose:    Specification of articulation parameters for moving
                and attached parts.
                In DIS version 7 onwards this data type is known as "Variable Parameters".
    size:       128 bits / 16
*********************************************************************/

#pragma once

#include "./DataTypeBase.h"

namespace KDIS {
namespace DATA_TYPE {

using KDIS::DATA_TYPE::ENUMS::ArticulationType;
using KDIS::DATA_TYPE::ENUMS::ArticulatedPartsHighBits;
using KDIS::DATA_TYPE::ENUMS::ArticulatedPartsLowBits;

class KDIS_EXPORT ArticulationParameters :  public DataTypeBase
{
protected:

    KUINT8 m_ui8ArticulationType;

    KUINT8 m_ui8ParmeterChange;

    KUINT16 m_ui16AttachementID;

    union
    {
        struct
        {
            KUINT16 m_VariantLowBits;
            KUINT16 m_VariantHighBits;
        };

        KUINT32 m_ui32ParamTypeVariant;
    } m_ui32ParamTypeVariantUnion;

    KUINT64 m_ui64ParamValue;

public:

    static const KUINT16 ARTICULATION_PARAMETERS_SIZE = 16;

    ArticulationParameters( void );

    ArticulationParameters( KDataStream & stream ) throw( KException );

    ArticulationParameters( ArticulationType AT, KUINT8 ParamChangeIndicator,
                            KUINT16 AttachID, KUINT32 TypeVariant, KUINT64 Value );

    virtual ~ArticulationParameters( void );

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::SetArticulationType
    //              KDIS::DATA_TYPE::ArticulationParameters::GetArticulationType
    // Description: Type.
    // Parameter:   ArticulationType AT, void
    //************************************
    void SetArticulationType( ArticulationType AT );
    ArticulationType GetArticulationType() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::SetParameterChangeIndicator
    //              KDIS::DATA_TYPE::ArticulationParameters::GetParameterChangeIndicator
    // Description: Stores change to any articulated part. Set to 0 at sim start and incremented
    //              each time a change occurs, if value > 255 it should be set back to 0.
    // Parameter:   KUINT8 PCI, void
    //************************************
    void SetParameterChangeIndicator( KUINT8 PCI );
    KUINT8 GetParameterChangeIndicator() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::SetAttachementID
    //              KDIS::DATA_TYPE::ArticulationParameters::GetAttachementID
    // Description: ID field of the articulated part to which the articulation parameter
    //              is attached. Field shall be 0 if the part is attached directly
    //              to the entity.
    // Parameter:   KUINT16 ID, void
    //************************************
    void SetAttachementID( KUINT16 ID );
    KUINT16 GetAttachementID() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::SetTypeVariantLowBits
    //              KDIS::DATA_TYPE::ArticulationParameters::GetTypeVariantLowBits
    // Description: Set the low bits value to the entity.
    // Parameter:   ArticulatedPartsLowBits VLB, void
    //************************************
    void SetTypeVariantLowBits( ArticulatedPartsLowBits VLB );
    ArticulatedPartsLowBits GetTypeVariantLowBits() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::SetTypeVariantHighBits
    //              KDIS::DATA_TYPE::ArticulationParameters::GetTypeVariantHighBits
    // Description: Set the high bits value to the entity.
    // Parameter:   ArticulatedPartsHighBits VHB, void
    //************************************
    void SetTypeVariantHighBits( ArticulatedPartsHighBits VHB );
    ArticulatedPartsHighBits GetTypeVariantHighBits() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::SetTypeVariant
    //              KDIS::DATA_TYPE::ArticulationParameters::GetTypeVariant
    // Description: Depends on Part type, only applies to Articulated parts.
    //              Not used for Attached parts.
    // Parameter:   KUINT32 TV, void
    //************************************
    void SetTypeVariant( KUINT32 TV );
    KUINT32 GetTypeVariant() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::SetValue
    //              KDIS::DATA_TYPE::ArticulationParameters::GetValue
    // Description: Value.
    // Parameter:   KUINT64 val, void
    //************************************
    void SetValue( KUINT64 val );
    KUINT64 GetValue() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::GetAsString
    // Description: Returns a string representation.
    //************************************
    virtual KString GetAsString() const;

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::Decode
    // Description: Convert From Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual void Decode( KDataStream & stream ) throw( KException );

    //************************************
    // FullName:    KDIS::DATA_TYPE::ArticulationParameters::Encode
    // Description: Convert To Network Data.
    // Parameter:   KDataStream & stream
    //************************************
    virtual KDataStream Encode() const;
    virtual void Encode( KDataStream & stream ) const;

    KBOOL operator == ( const ArticulationParameters & Value ) const;
    KBOOL operator != ( const ArticulationParameters & Value ) const;
};

}; // END namespace DATA_TYPES
}; // END namespace KDIS
