#pragma once
#define PSW_ONLY_EVENT			// �̺�Ʈ ���� ������ �̰ɷ� ������ ���� ����.( 2008.03.30 )
#ifdef	PSW_ONLY_EVENT 

/*----------------------------------- �̺�Ʈ --------------------------------------*/


// 07�� �߼��̺�Ʈ (2007.08.24)
#define PRUARIN_EVENT07_3COLORHARVEST			

// ���ɳ��� �̺�Ʈ(2008.03.12)
#define CSK_EVENT_CHERRYBLOSSOM							    
#ifdef CSK_EVENT_CHERRYBLOSSOM
	#define ADD_GLOBAL_MIX_MAR08						    // �ؿ� ī����ī��, ���� ���� ���� ��ũ��Ʈ Ȯ��-�������� ���� Ȯ�� (2008.03.21) [mix.txt ��ġ�ؾߵ�]
	#define PSW_EVENT_CHERRYBLOSSOMTREE					    // ���ɳ��� �߰� ���� ������ ( 2008.04.03 )
	#define PBG_FIX_GOLD_CHERRYBLOSSOMTREE					// ���ɳ��� �������� �� ���ߴ� ���� ����(2009.03.26)
#endif CSK_EVENT_CHERRYBLOSSOM

// �Ϻ� ���� Ȳ�� �ü� �̺�Ʈ
#if SELECTED_LANGUAGE == LANGUAGE_JAPANESE || SELECTED_LANGUAGE == LANGUAGE_ENGLISH
	#define PSW_GOLDBOWMAN									// �Ϻ� ���� Ȳ�� �ü� ���� �̺�Ʈ
	#define PSW_EVENT_LENA									// �Ϻ� ���� Ȳ�� �ü� ���� �̺�Ʈ
	#define YDG_ADD_GOLDBOWMAN_INVENTORY_SPACE_CHECK		// �Ϻ� ���� Ȳ�� �ü� �κ��丮 �˻� (2*4) (2008.12.02)
#endif //SELECTED_LANGUAGE == LANGUAGE_JAPANES

/*--------------------------------- �̺�Ʈ �� --------------------------------------*/

#endif //PSW_ONLY_EVENT