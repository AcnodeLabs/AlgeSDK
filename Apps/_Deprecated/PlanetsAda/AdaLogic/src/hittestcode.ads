with Interfaces.C; use Interfaces.C;
with Ada.Containers;
with Ada.Containers; use Ada.Containers;
with Ada.Containers.Vectors;
with Text_IO; use Text_IO;

package HitTestCode is

   type FloatBounds is tagged
    record
         name: Int;
         xMin: Float;
         xMax: Float;
         yMin: Float;
         yMax: Float;
   end record;

   package HitList is new Vectors(Natural, FloatBounds);
   use HitList;

   procedure HitTest (aCursor : Cursor);
   function DoIt(fX : Float; fY : Float) return Integer;

   hitCursor : HitList.Cursor;
   hitBounds : HitList.Vector;

end HitTestCode;
