class RscInGameUI
{
  class RscUnitInfoSoldier;
  class RscWeaponZeroing;
  //not needed anymore, leaving for the sake of compability.
  class Niarms_Rsc_AltReload_Zeroing: RscWeaponZeroing
  {
    idd = 9640;
    onLoad="['onLoad',_this,'RscUnitInfo','IGUI'] call (uinamespace getvariable 'BIS_fnc_initDisplay'); _this call Niarms_altReloads_fnc_postInit;";
  };
};
