# NIArms

Alternative reloads allows you to have different model.cfg and hand gesture reload animations for a single weapon.
To achieve this you need to make multiple copies of the weapon depending on how many animation variations you want.
Once this is done you set up class names for them as you would any other weapon (keep them scope 1 obviously).

Inside the 'real' weapon config you need to define some classes, example:
```cpp
class NIArms_Alt_Reloads //The main class, without this it won't work
{
  class LIB_LeeEnfield_No4 //A weapon class name, the class name to be used if the condition below is true
  {
    condition = "(%1 == 0 || %1 == 10)"; //Condition, %1 is the ammo in the currently loaded magazine, so in this example if the weapon is empty or full, use the default class, which will skip the system entirely.
  };
  class LIB_LeeEnfield_No4_altReload1 // Each condition is checked in order, and the first one to return true will be used, but it's good practice to keep it so only one is true.
  {
    condition = "(%1 > 6)";
  };
  class LIB_LeeEnfield_No4_altReload2
  {
    condition = "((%1 <= 6) && (%1 > 4))";
  };
};
```
If no conditions return true, it will simply default to engine reloading!

Keep the reload classes simple and identical to their parent class.
Example:
```cpp
class LIB_LeeEnfield_No4_altReload1: LIB_LeeEnfield_No4
{
  scope = 1;
  baseweapon = "LIB_LeeEnfield_No4"; //This ensures stuff like arsenal hides it
  reloadAction = "LIB_GestureReload_Common_sniper";
  model = "\WW2\Assets_m\Weapons\Rifles_m\DD_Enfield_No4_altReload1.p3d";
  reloadMagazineSound[] = {"\WW2\Assets_s\Weapons\Rifles_s\BoltAction\Reload_sniper.wss",1,1,10};
};
```

In 191 Bohemia have added reload and reloaded eventhandlers to weapons, the script supports this and its highly recommended you add the 'reload' handler as the script will automatically disable the 'old' PerFrame method and opt to use the reload handler instead if the function is available. To do this simply add the eventhandler as follows:
```cpp
class LIB_LeeEnfield_No4: LIB_RIFLE
{
  class Eventhandlers: Eventhandlers
  {
    class NIArms_Alt_Reloads
    {
      reload = "_this call NIArms_altReloads_fnc_onReload";
	  Reloaded = "_this call NIArms_altReloads_fnc_afterReload";
    };
  };
};
```
A Reloaded handler is also needed, it can be set either in the weapon (post 191) or on the unit itself. Example:
```cpp
class CAManBase: Man
{
  class EventHandlers: EventHandlers
  {
    class NIArms_altReloads
    {
      Reloaded = "_this call NIArms_altReloads_fnc_afterReload";
    };
};
```
