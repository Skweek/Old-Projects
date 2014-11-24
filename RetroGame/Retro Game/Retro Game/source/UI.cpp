#include "Game.h"
#include "UI.h"
#include "Enums.h"
#include "AIE.h"

UI::UI( Game* GameHandle )
{
	m_pGameHandle = GameHandle;
	m_uiUI = m_pGameHandle->GetSprite( MENU_SPRITE );
}

void UI::Update()
{
	switch ( m_pGameHandle->GetMenuState() )
	{
	case SPLASHSCREEN_STATE:
		break;

	case MAINMENU_STATE:
		break;

	case PAUSEMENU_STATE:
		break;

	case HIGHSCORES_STATE:
		break;

	case PLAYERDEAD_STATE:
		 break;

	case LEVELCOMPLETE_STATE:
		break;

	default:
		break;
	}

	Draw();
}

void UI::Draw()
{
	MoveSprite( m_uiUI, 0.f, 0.f );
	DrawSprite( m_uiUI );
}