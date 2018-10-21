-- ATimed.ads
package CTimed is
   function dst(vel: Float; dt: Float) return Float;
   function spd(dst: Float; dt: Float)  return Float;

   type CTimedT is tagged
      record
       curr1, from1, to1, speed1 : Float := 0.0;
       done : Boolean := False;
      end record;

   procedure Set( from: Float; to: Float; speed : Float; ct: in out CTimedT'Class);
   procedure Redo( ct : in out CTimedT'Class);
   function StepLinear(dt: Float; ct : in out CTimedT'Class) return Float;

end CTimed;
