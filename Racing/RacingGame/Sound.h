#pragma once
#include <windows.h>    //Ű���� �Է�
#pragma comment (lib, "winmm.lib")    //����
#include <mmsystem.h>;                //����
#include <Digitalv.h>;                //����

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openShuffleSound;
MCI_PLAY_PARMS playShuffleSound;

#define BGM_1 "C:\\Users\\kimdg\\Desktop\\c++pj\\Racing\\RacingGame\\BGM_1.wav"    //ù���� BGM
#define BGM_2 "C:\\Users\\kimdg\\Desktop\\c++pj\\Racing\\RacingGame\\BGM_2.wav"    //�ι�° BGM
#define BGM_3 "C:\\Users\\kimdg\\Desktop\\c++pj\\Racing\\RacingGame\\BGM_3.wav"

int dwID;

//void playingBgm(void) {
//    openBgm.lpstrElementName = BGM_1;            //���� ����
//    openBgm.lpstrDeviceType ="mpegvideo";    //mp3 ����
//    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
//    dwID = openBgm.wDeviceID;
//    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);    //���� �ݺ� ���
//}
//void playingShuffleSound(void) {
//    openShuffleSound.lpstrElementName = BGM_2;    //���� ����
//    openShuffleSound.lpstrDeviceType = "mpegvideo";    //mp3 ����
//    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openShuffleSound);
//    dwID = openShuffleSound.wDeviceID;
//    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openShuffleSound);    //������ �� �� ���
//    Sleep(1800);    //ȿ������ ����� ������ �����ߴٰ�
//    mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);    //���� ��� ��ġ�� ó������ �ʱ�ȭ
//}