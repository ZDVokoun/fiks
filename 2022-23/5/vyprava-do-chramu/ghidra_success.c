
undefined4 __cdecl success(char *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_30;
  undefined local_2c;
  undefined4 local_2b;
  undefined4 local_27;
  undefined4 local_23;
  undefined4 local_1f;
  undefined4 local_1b;
  undefined4 local_17;
  undefined4 local_13;
  uint local_c;
  ushort local_8 [2];
  
  iVar2 = 0x21;
  local_30 = 0x1a091034;
  local_8[0] = 0;
  local_2c = 0x21;
  local_2b = 0x610f0707;
  local_27 = 0x2c59180b;
  local_23 = 0xd100c14;
  local_1f = 0x2a365113;
  local_1b = 0x260a5207;
  local_17 = 0x28193d4a;
  local_13 = 0x2f180f44;
  print("\nGratulujeme! Tajemstvi je\n");
  uVar1 = strlen(param_1);
  uVar3 = 0;
  local_c = uVar1 & 0xffff;
  do {
    local_8[0] = local_8[0] & 0xff00 |
                 (ushort)(byte)(param_1[uVar3 % local_c] ^ *(byte *)((int)&local_30 + uVar3));
    print((char *)local_8);
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  print("\n");
  return 0;
}

