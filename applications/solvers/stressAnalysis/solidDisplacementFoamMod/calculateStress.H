if (runTime.writeTime())
{
    volSymmTensorField sigma
    (
        IOobject
        (
            "sigma",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        rho*sigmaD
    );

    if (thermo.thermalStress())
    {
        sigma = sigma - I*(rho*threeKalpha*thermo.T());
    }

    volScalarField sigmaEq
    (
        IOobject
        (
            "sigmaEq",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        sqrt((3.0/2.0)*magSqr(dev(sigma)))
    );

//    Info<< "sigmaEq = " << sigmaEq << endl;
    Info<< "Max sigmaEq = " << max(sigmaEq).value()
        << endl;


//    Info<< "D = " << D << endl;
    // FIXME Hardcoded to specifiec beam end load case
    Info<< "Max D = " << min(D).value() << endl;


    runTime.write();
}
