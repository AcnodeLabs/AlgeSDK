package body CAnimator is

   function LinearTween(t: Float; starts:Float; ends:Float) return Float is
   begin
      if t>=1.0 then return ends; end if;
      return t*ends+(1.0-t)*starts;
   end LinearTween;

   function QuadraticEaseIn(t: Float; starts:Float; ends:Float) return Float is
      begin
      return LinearTween(t*t,starts,ends);
   end QuadraticEaseIn;

   function QuadraticEaseInOut(t: Float; starts:Float; ends:Float) return Float is
      middle: Float := 0.0;
      tt: Float := 0.0;
   begin
      tt:=t;
      middle:=(starts+ends)/2.0;
      tt:=2.0*t;
      if tt <= 1.0 then return LinearTween(tt*tt,starts,middle); end if;
      tt:= tt-1.0;
   return LinearTween(tt*tt,middle,ends);
end QuadraticEaseInOut;

   function LinearTween(t: Float; starts:vec2; ends:vec2) return vec2 is
      r: vec2;
   begin
     r(0) := LinearTween(t, starts(0), ends(0));
     r(1) := LinearTween(t, starts(1), ends(1));
     return r;
   end LinearTween;

   function QuadraticEaseIn(t: Float; starts:vec2; ends:vec2) return vec2 is
      r: vec2;
   begin
     r(0) := QuadraticEaseIn(t, starts(0), ends(0));
     r(1) := QuadraticEaseIn(t, starts(1), ends(1));
     return r;
   end QuadraticEaseIn;

   function QuadraticEaseInOut(t: Float; starts:vec2; ends:vec2) return vec2 is
       r: vec2;
   begin
      r(0) := QuadraticEaseInOut(t, starts(0), ends(0));
      r(1) := QuadraticEaseInOut(t, starts(1), ends(1));
    return r;
   end QuadraticEaseInOut;

   procedure Reset(current: vec3; desirable:  vec3; speedA: Float; can :in out CAnim'Class) is
   begin
      can.tTotal     := Dist(current,desirable) / speedA;

      can.curr       := current;
      can.speed      := speedA;

      can.desired(0) := desirable(0);
      can.desired(1) := desirable(1);
      can.desired(2) := desirable(2);

      can.start(0)     := current(0);
      can.start(1)     := current(1);
      can.start(2)     := current(2);

      can.tRun       := 0.0;

      can.active     := true;
   end Reset;

   procedure Step(dt: Float; can :in out CAnim'Class) is
    begin
      if can.active then can.tRun := can.tRun + dt; else can.tTotal := 0.0;return; end if;
      can.r := can.tRun / can.tTotal;
      can.curr(0) := LinearTween(can.r, can.start(0), can.desired(0));
      can.curr(1) := LinearTween(can.r, can.start(1), can.desired(1));
      can.curr(2) := LinearTween(can.r, can.start(2), can.desired(2));
      if can.r>=1.0 then can.active := false; end if;
   end Step;

   function Sqr(x: Float) return Float is
    begin
      return x*x;
   end Sqr;

   function Dist(current :vec3; desired: vec3) return Float is
    begin
      return   Ada.Numerics.Elementary_Functions.Sqrt(
                            Sqr(desired(0)-current(0))
                          + Sqr(desired(1)-current(1))
                          + Sqr(desired(2)-current(1))
                         );
   end Dist;

end CAnimator;
