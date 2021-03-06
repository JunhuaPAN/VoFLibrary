/*---------------------------------------------------------------------------*\
            Copyright (c) 2017-2019, German Aerospace Center (DLR)
-------------------------------------------------------------------------------
License
    This file is part of the VoFLibrary source code library, which is an 
	unofficial extension to OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.
    
Class
    Foam::implicitFunction::impDisc

Description
    creates a infintite long cylinder

Author
    Henning Scheufler, DLR, all rights reserved.

SourceFiles
    impDisc.C

\*---------------------------------------------------------------------------*/

#ifndef impDisc_H
#define impDisc_H

#include "implicitFunctions.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace implicitFunction
{
// Forward declaration of classes

/*---------------------------------------------------------------------------*\
                           Class impDisc Declaration
\*---------------------------------------------------------------------------*/

class impDisc
:
    public implicitFunctions
{
private:

    // Private Member Data

        //- Centre point
        const point centre_;

        //- Radius
        const scalar radius_;

        const scalar scale_;

        vector direction_;

        tensor project_;

    // Private Member Functions

        //- Disallow default bitwise copy construct
        impDisc(const impDisc&);

        //- Disallow default bitwise assignment
        void operator=(const impDisc&);


public:

    //- Runtime type information
    TypeName("disc");


    // Constructors

        //- Construct from components
        impDisc( const point&, const scalar radius,const scalar scale,const vector direction);

        //- Construct from dictionary (used by implicitFunctions)
        impDisc
        (
            const dictionary& dict
        );

    //- Destructor
    virtual ~impDisc();

    virtual scalar value(const vector p) 
    {
          return (-mag(project_ & (p-centre_))+radius_)*scale_;
    }

    virtual vector grad(const vector p) 
    {
        return -(project_ & (p-centre_))*scale_;
    }

    virtual scalar distanceToSurfaces(const vector p) 
    {
        return mag(mag(project_ & (p-centre_))-radius_)*scale_;
    }


    // Member Functions


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
} // End namespace implicitFunction
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
