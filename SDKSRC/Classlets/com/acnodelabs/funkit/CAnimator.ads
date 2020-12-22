with Ada.Numerics.Elementary_Functions;
use Ada.Numerics.Elementary_Functions;

package CAnimator is
   type vec3 is array (0..2) of Float;
   type vec2 is array (0..1) of Float;

   type CAnim is tagged
     record
   speed :Float:=0.0;
   curr, desired, d, v,start : vec3;
   active : Boolean;
   r,tTotal,tRun:Float;
      end record;

   function LinearTween(t: Float; starts:Float; ends:Float) return Float;
   function QuadraticEaseIn(t: Float; starts:Float; ends:Float) return Float;
   function QuadraticEaseInOut(t: Float; starts:Float; ends:Float) return Float;

   function LinearTween(t: Float; starts:vec2; ends:vec2) return vec2;
   function QuadraticEaseIn(t: Float; starts:vec2; ends:vec2) return vec2;
   function QuadraticEaseInOut(t: Float; starts:vec2; ends:vec2) return vec2;

   procedure Reset(current: vec3; desirable:  vec3; speedA: Float; can: in out CAnim'Class);
   procedure Step(dt: Float; can: in out CAnim'Class);
   function Sqr(x: Float) return Float;
   function Dist(current :vec3; desired: vec3) return Float;

end CAnimator;
