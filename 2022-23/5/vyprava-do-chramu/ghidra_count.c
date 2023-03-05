
int __cdecl FUN_00401334(char *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    iVar1 = iVar1 * 10 + -0x30 + (int)*param_1;
  }
  return iVar1;
}

