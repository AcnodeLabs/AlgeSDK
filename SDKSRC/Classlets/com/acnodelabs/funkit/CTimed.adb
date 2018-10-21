-- ATimed.adb
package body CTimed is

   function dst(vel: Float; dt: Float) return Float is
   begin
      return 0.0;
   end dst;

   function spd(dst: Float; dt: Float)  return Float is
         begin
      return 0.0;
   end spd;

   procedure Set( from: Float; to: Float; speed : Float; ct: in out CTimedT'Class) is
   begin
      ct.curr1 := from;
      ct.from1 := from;
      ct.to1 := to;
      ct.speed1 := speed;
   end Set;

   procedure Redo( ct : in out CTimedT'Class) is
     begin
     ct.curr1 := ct.from1;
   end Redo;

   function StepLinear(dt: Float; ct: in out CTimedT'Class) return Float is
      i1 : Float := 0.0;
   begin
      if ct.done then
         return ct.to1;
      else
         if ct.from1>ct.to1 then i1:=-1.0; else i1:=1.0; end if;
         ct.curr1 := ct.curr1 + i1 * abs(ct.speed1) * dt;
         if ct.to1>ct.from1 and ct.curr1>=ct.to1 then ct.done:=True; end if;
         if ct.to1<ct.from1 and ct.curr1<=ct.to1 then ct.done:=True; end if;
         if ct.to1=ct.from1 then ct.done := True; end if;
      end if;
      return ct.curr1;
   end StepLinear;


end CTimed;
