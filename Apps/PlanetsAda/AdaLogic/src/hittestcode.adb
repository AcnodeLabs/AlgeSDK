package body HitTestCode is

  fUnassigned : constant Float := -1.0;

   touchedX : Float := fUnassigned;
   touchedY : Float := fUnassigned;
   lastHitName : Integer := 0;

   -- e.g  HitTestCode.DoIt(Float(i1)/ Float(1190), Float(i2)/ Float(700));
   -- returns lastHitName
   function DoIt (fX : Float; fY : Float) return Integer is
   begin
      touchedX := fX;
      touchedY := fY;
      lastHitName := 0;
      Iterate(Container => hitBounds, Process => HitTest'Access);
      touchedX := fUnassigned;
      touchedY := fUnassigned;
      return lastHitName;
   end DoIt;

   procedure HitTest (aCursor : Cursor)  is
    aBound : constant FloatBounds := Element (Position => aCursor);
   begin

      if (touchedX >= aBound.xMin and touchedX <= aBound.xMax and
         touchedY >= aBound.yMin and touchedY <= aBound.yMax) then
         lastHitName := Integer(aBound.name);
      end if;

   end HitTest;
begin
   null;
end HitTestCode;
