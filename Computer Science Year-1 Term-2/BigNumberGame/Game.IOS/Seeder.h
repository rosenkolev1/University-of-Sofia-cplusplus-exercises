#pragma once
class Seeder
{
	/*
Admin1^Admin1^Admin^0^3^COL_NULL^TRUE^FALSE\n
roskata123^pederas^Normal^0^3^COL_NULL^TRUE^FALSE\n
Roskata123^Pederas^Normal^2^1^COL_NULL^TRUE^FALSE\n
Roskata12^pederasNov^Normal^0^3^COL_NULL^TRUE^FALSE\n
NovUser^NovUser^Normal^0^3^COL_NULL^TRUE^FALSE\n
SomeNewUser^NewPassword^Normal^0^3^COL_NULL^TRUE^TRUE\n
SomeStupidUser^Stupid^Normal^0^3^COL_NULL^TRUE^FALSE\n
	*/

public:
	static void seedDatabase(bool overwrite);
};

