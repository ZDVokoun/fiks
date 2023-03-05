
undefined4 entry(void)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  char *pcVar5;
  char local_104;
  char local_103;
  char local_102;
  char local_101;
  char local_100;
  char local_ff;
  char local_fe;
  char local_fd;
  char local_fc;
  
  print(
       "V tomhle programu se schovava tajemstvi. K jeho ziskani musis zadat spravne heslo. A jak heslo zjistis?\nReverse engineering! Dobry zacatek je prozkoumat program hezky instrukci po instrukci.\nPomoci ti mohou nastroje jako OllyDBG, Ida Free, Radare2 nebo Ghidra.\n-------------------------------------------------------------------------------------------------------\nZadej heslo: "
       );
  iVar2 = input(&local_104);
  if (iVar2 != 0) {
    Sleep(0xfa);
    sVar1 = strlen(&local_104);
    if ((ushort)(sVar1 - 8U) < 3) {
      if ((local_fc == '\0') || (local_fc == '\r')) {
        iVar2 = (int)local_102;
        local_fc = '\0';
        uVar3 = FUN_00401334("117");
        if (((((int)local_104 + (int)local_100 == 0xac) &&
             ((((';' < local_100 && (local_103 == local_fd)) && (Sleep(0xfa), local_101 == 'i')) &&
              (((int)local_fd - (int)local_fe == 0x17 &&
               ((int)local_102 + iVar2 * -2 + (int)local_fe == 0)))))) &&
            ((int)local_ff == (uVar3 & 0xffff))) && ((local_103 == 'y' && (local_100 < '[')))) {
          uVar4 = success(&local_104);
          return uVar4;
        }
      }
      pcVar5 = "\nSpatne heslo!\n";
      goto LAB_00401531;
    }
  }
  pcVar5 = "\nSpatna delka hesla!\n";
LAB_00401531:
  print(pcVar5);
  return 1;
}

