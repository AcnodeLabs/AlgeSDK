pragma Ada_95;
pragma Warnings (Off);
pragma Source_File_Name (ada_main, Spec_File_Name => "b__alge-gnat-mac.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__alge-gnat-mac.adb");
pragma Suppress (Overflow_Check);

with System.Restrictions;
with Ada.Exceptions;

package body ada_main is

   E116 : Short_Integer; pragma Import (Ada, E116, "system__os_lib_E");
   E021 : Short_Integer; pragma Import (Ada, E021, "system__soft_links_E");
   E031 : Short_Integer; pragma Import (Ada, E031, "system__exception_table_E");
   E122 : Short_Integer; pragma Import (Ada, E122, "ada__containers_E");
   E095 : Short_Integer; pragma Import (Ada, E095, "ada__io_exceptions_E");
   E069 : Short_Integer; pragma Import (Ada, E069, "ada__strings_E");
   E075 : Short_Integer; pragma Import (Ada, E075, "ada__strings__maps_E");
   E013 : Short_Integer; pragma Import (Ada, E013, "ada__tags_E");
   E094 : Short_Integer; pragma Import (Ada, E094, "ada__streams_E");
   E114 : Short_Integer; pragma Import (Ada, E114, "interfaces__c_E");
   E121 : Short_Integer; pragma Import (Ada, E121, "interfaces__c__strings_E");
   E033 : Short_Integer; pragma Import (Ada, E033, "system__exceptions_E");
   E119 : Short_Integer; pragma Import (Ada, E119, "system__file_control_block_E");
   E112 : Short_Integer; pragma Import (Ada, E112, "system__file_io_E");
   E097 : Short_Integer; pragma Import (Ada, E097, "system__finalization_root_E");
   E092 : Short_Integer; pragma Import (Ada, E092, "ada__finalization_E");
   E099 : Short_Integer; pragma Import (Ada, E099, "system__storage_pools_E");
   E087 : Short_Integer; pragma Import (Ada, E087, "system__finalization_masters_E");
   E085 : Short_Integer; pragma Import (Ada, E085, "system__storage_pools__subpools_E");
   E025 : Short_Integer; pragma Import (Ada, E025, "system__secondary_stack_E");
   E071 : Short_Integer; pragma Import (Ada, E071, "ada__strings__unbounded_E");
   E159 : Short_Integer; pragma Import (Ada, E159, "system__tasking__initialization_E");
   E183 : Short_Integer; pragma Import (Ada, E183, "ada__real_time_E");
   E107 : Short_Integer; pragma Import (Ada, E107, "ada__text_io_E");
   E167 : Short_Integer; pragma Import (Ada, E167, "system__tasking__protected_objects_E");
   E171 : Short_Integer; pragma Import (Ada, E171, "system__tasking__protected_objects__entries_E");
   E175 : Short_Integer; pragma Import (Ada, E175, "system__tasking__queuing_E");
   E181 : Short_Integer; pragma Import (Ada, E181, "system__tasking__stages_E");
   E003 : Short_Integer; pragma Import (Ada, E003, "algesdk_E");
   E002 : Short_Integer; pragma Import (Ada, E002, "adaapp_E");
   E009 : Short_Integer; pragma Import (Ada, E009, "t_E");
   E007 : Short_Integer; pragma Import (Ada, E007, "t__th_E");

   Local_Priority_Specific_Dispatching : constant String := "";
   Local_Interrupt_States : constant String := "";

   Is_Elaborated : Boolean := False;

   procedure finalize_library is
   begin
      declare
         procedure F1;
         pragma Import (Ada, F1, "algesdk__finalize_spec");
      begin
         E003 := E003 - 1;
         if E003 = 0 then
            F1;
         end if;
      end;
      E171 := E171 - 1;
      declare
         procedure F2;
         pragma Import (Ada, F2, "system__tasking__protected_objects__entries__finalize_spec");
      begin
         if E171 = 0 then
            F2;
         end if;
      end;
      E107 := E107 - 1;
      declare
         procedure F3;
         pragma Import (Ada, F3, "ada__text_io__finalize_spec");
      begin
         if E107 = 0 then
            F3;
         end if;
      end;
      E071 := E071 - 1;
      declare
         procedure F4;
         pragma Import (Ada, F4, "ada__strings__unbounded__finalize_spec");
      begin
         if E071 = 0 then
            F4;
         end if;
      end;
      declare
         procedure F5;
         pragma Import (Ada, F5, "system__file_io__finalize_body");
      begin
         E112 := E112 - 1;
         if E112 = 0 then
            F5;
         end if;
      end;
      E087 := E087 - 1;
      E085 := E085 - 1;
      declare
         procedure F6;
         pragma Import (Ada, F6, "system__storage_pools__subpools__finalize_spec");
      begin
         if E085 = 0 then
            F6;
         end if;
      end;
      declare
         procedure F7;
         pragma Import (Ada, F7, "system__finalization_masters__finalize_spec");
      begin
         if E087 = 0 then
            F7;
         end if;
      end;
      declare
         procedure Reraise_Library_Exception_If_Any;
            pragma Import (Ada, Reraise_Library_Exception_If_Any, "__gnat_reraise_library_exception_if_any");
      begin
         Reraise_Library_Exception_If_Any;
      end;
   end finalize_library;

   procedure adafinal is

      procedure Runtime_Finalize;
      pragma Import (C, Runtime_Finalize, "__gnat_runtime_finalize");

   begin
      if not Is_Elaborated then
         return;
      end if;
      Is_Elaborated := False;
      Runtime_Finalize;
      finalize_library;
   end adafinal;

   type No_Param_Proc is access procedure;

   procedure adainit is
      Main_Priority : Integer;
      pragma Import (C, Main_Priority, "__gl_main_priority");
      Time_Slice_Value : Integer;
      pragma Import (C, Time_Slice_Value, "__gl_time_slice_val");
      WC_Encoding : Character;
      pragma Import (C, WC_Encoding, "__gl_wc_encoding");
      Locking_Policy : Character;
      pragma Import (C, Locking_Policy, "__gl_locking_policy");
      Queuing_Policy : Character;
      pragma Import (C, Queuing_Policy, "__gl_queuing_policy");
      Task_Dispatching_Policy : Character;
      pragma Import (C, Task_Dispatching_Policy, "__gl_task_dispatching_policy");
      Priority_Specific_Dispatching : System.Address;
      pragma Import (C, Priority_Specific_Dispatching, "__gl_priority_specific_dispatching");
      Num_Specific_Dispatching : Integer;
      pragma Import (C, Num_Specific_Dispatching, "__gl_num_specific_dispatching");
      Main_CPU : Integer;
      pragma Import (C, Main_CPU, "__gl_main_cpu");
      Interrupt_States : System.Address;
      pragma Import (C, Interrupt_States, "__gl_interrupt_states");
      Num_Interrupt_States : Integer;
      pragma Import (C, Num_Interrupt_States, "__gl_num_interrupt_states");
      Unreserve_All_Interrupts : Integer;
      pragma Import (C, Unreserve_All_Interrupts, "__gl_unreserve_all_interrupts");
      Detect_Blocking : Integer;
      pragma Import (C, Detect_Blocking, "__gl_detect_blocking");
      Default_Stack_Size : Integer;
      pragma Import (C, Default_Stack_Size, "__gl_default_stack_size");
      Leap_Seconds_Support : Integer;
      pragma Import (C, Leap_Seconds_Support, "__gl_leap_seconds_support");
      Bind_Env_Addr : System.Address;
      pragma Import (C, Bind_Env_Addr, "__gl_bind_env_addr");

      procedure Runtime_Initialize (Install_Handler : Integer);
      pragma Import (C, Runtime_Initialize, "__gnat_runtime_initialize");

      Finalize_Library_Objects : No_Param_Proc;
      pragma Import (C, Finalize_Library_Objects, "__gnat_finalize_library_objects");
   begin
      if Is_Elaborated then
         return;
      end if;
      Is_Elaborated := True;
      Main_Priority := -1;
      Time_Slice_Value := -1;
      WC_Encoding := 'b';
      Locking_Policy := ' ';
      Queuing_Policy := ' ';
      Task_Dispatching_Policy := ' ';
      System.Restrictions.Run_Time_Restrictions :=
        (Set =>
          (False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, True, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False),
         Value => (0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
         Violated =>
          (False, False, False, True, True, False, False, False, 
           False, False, False, True, True, True, False, False, 
           True, False, False, True, True, False, True, True, 
           False, True, True, True, True, False, False, False, 
           False, False, True, False, False, True, False, True, 
           False, False, True, False, False, False, True, True, 
           False, False, True, False, False, False, False, False, 
           False, False, True, True, True, True, True, False, 
           False, True, False, True, True, True, False, True, 
           True, False, True, True, True, True, False, False, 
           True, False, False, False, False, True, True, True, 
           False, False, False),
         Count => (0, 0, 0, 0, 2, 1, 1, 0, 0, 0),
         Unknown => (False, False, False, False, False, False, False, False, False, False));
      Priority_Specific_Dispatching :=
        Local_Priority_Specific_Dispatching'Address;
      Num_Specific_Dispatching := 0;
      Main_CPU := -1;
      Interrupt_States := Local_Interrupt_States'Address;
      Num_Interrupt_States := 0;
      Unreserve_All_Interrupts := 0;
      Detect_Blocking := 0;
      Default_Stack_Size := -1;
      Leap_Seconds_Support := 0;

      Runtime_Initialize (1);

      if E021 = 0 then
         System.Soft_Links'Elab_Spec;
      end if;
      if E031 = 0 then
         System.Exception_Table'Elab_Body;
      end if;
      E031 := E031 + 1;
      if E122 = 0 then
         Ada.Containers'Elab_Spec;
      end if;
      E122 := E122 + 1;
      if E095 = 0 then
         Ada.Io_Exceptions'Elab_Spec;
      end if;
      E095 := E095 + 1;
      if E069 = 0 then
         Ada.Strings'Elab_Spec;
      end if;
      E069 := E069 + 1;
      if E075 = 0 then
         Ada.Strings.Maps'Elab_Spec;
      end if;
      if E013 = 0 then
         Ada.Tags'Elab_Spec;
      end if;
      if E094 = 0 then
         Ada.Streams'Elab_Spec;
      end if;
      E094 := E094 + 1;
      if E114 = 0 then
         Interfaces.C'Elab_Spec;
      end if;
      if E121 = 0 then
         Interfaces.C.Strings'Elab_Spec;
      end if;
      if E033 = 0 then
         System.Exceptions'Elab_Spec;
      end if;
      E033 := E033 + 1;
      if E119 = 0 then
         System.File_Control_Block'Elab_Spec;
      end if;
      E119 := E119 + 1;
      if E097 = 0 then
         System.Finalization_Root'Elab_Spec;
      end if;
      E097 := E097 + 1;
      if E092 = 0 then
         Ada.Finalization'Elab_Spec;
      end if;
      E092 := E092 + 1;
      if E099 = 0 then
         System.Storage_Pools'Elab_Spec;
      end if;
      E099 := E099 + 1;
      if E087 = 0 then
         System.Finalization_Masters'Elab_Spec;
      end if;
      if E085 = 0 then
         System.Storage_Pools.Subpools'Elab_Spec;
      end if;
      E085 := E085 + 1;
      if E087 = 0 then
         System.Finalization_Masters'Elab_Body;
      end if;
      E087 := E087 + 1;
      if E112 = 0 then
         System.File_Io'Elab_Body;
      end if;
      E112 := E112 + 1;
      E121 := E121 + 1;
      E114 := E114 + 1;
      if E013 = 0 then
         Ada.Tags'Elab_Body;
      end if;
      E013 := E013 + 1;
      E075 := E075 + 1;
      if E021 = 0 then
         System.Soft_Links'Elab_Body;
      end if;
      E021 := E021 + 1;
      if E116 = 0 then
         System.Os_Lib'Elab_Body;
      end if;
      E116 := E116 + 1;
      if E025 = 0 then
         System.Secondary_Stack'Elab_Body;
      end if;
      E025 := E025 + 1;
      if E071 = 0 then
         Ada.Strings.Unbounded'Elab_Spec;
      end if;
      E071 := E071 + 1;
      if E159 = 0 then
         System.Tasking.Initialization'Elab_Body;
      end if;
      E159 := E159 + 1;
      if E183 = 0 then
         Ada.Real_Time'Elab_Spec;
      end if;
      if E183 = 0 then
         Ada.Real_Time'Elab_Body;
      end if;
      E183 := E183 + 1;
      if E107 = 0 then
         Ada.Text_Io'Elab_Spec;
      end if;
      if E107 = 0 then
         Ada.Text_Io'Elab_Body;
      end if;
      E107 := E107 + 1;
      if E167 = 0 then
         System.Tasking.Protected_Objects'Elab_Body;
      end if;
      E167 := E167 + 1;
      if E171 = 0 then
         System.Tasking.Protected_Objects.Entries'Elab_Spec;
      end if;
      E171 := E171 + 1;
      if E175 = 0 then
         System.Tasking.Queuing'Elab_Body;
      end if;
      E175 := E175 + 1;
      if E181 = 0 then
         System.Tasking.Stages'Elab_Body;
      end if;
      E181 := E181 + 1;
      if E003 = 0 then
         Algesdk'Elab_Spec;
      end if;
      E003 := E003 + 1;
      if E002 = 0 then
         Adaapp'Elab_Body;
      end if;
      E002 := E002 + 1;
      if E007 = 0 then
         t.th'elab_spec;
      end if;
      if E007 = 0 then
         t.th'elab_body;
      end if;
      E007 := E007 + 1;
      E009 := E009 + 1;
   end adainit;

--  BEGIN Object file/option list
   --   /Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/CMD.o
   --   /Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/AlgeSDK.o
   --   /Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/AdaApp.o
   --   /Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/structdefs_h.o
   --   /Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/t-th.o
   --   /Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/t.o
   --   -L/Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/
   --   -L/Users/alex/Desktop/AlgeSDK_1701/Platforms/Alge-Gnat-macOS/obj/
   --   -L/usr/local/gnat/lib/gcc/x86_64-apple-darwin14.5.0/4.9.4/adalib/
   --   -static
   --   -lgnarl
   --   -lgnat
--  END Object file/option list   

end ada_main;
