-- generated using g++ -c -fdump-ada-spec "StructDefs.h" -C

pragma Style_Checks (Off);

with Interfaces.C; use Interfaces.C;

package StructDefs_h is

   type MoonInfo is record
      Year_Discovered : aliased int;  -- StructDefs.h:2
      Distance_From_Planet_km : aliased int;  -- StructDefs.h:3
      Diameter_km : aliased int;  -- StructDefs.h:4
      Orbital_Period_days : aliased float;  -- StructDefs.h:5
   end record;
   pragma Convention (C_Pass_By_Copy, MoonInfo);  -- StructDefs.h:1

end StructDefs_h;
