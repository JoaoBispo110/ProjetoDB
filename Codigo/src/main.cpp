#include "Persistencia.h"
#include "Interface.h"

int main(){
	Persistencia* persistencia = &Persistencia::GetInstance();
	Interface* interface = &Interface::GetInstance();
	Options opt;

	interface->Login();

	do{
		opt = interface->Menu();

		switch(opt){
			case Log_Off:
				interface->Login();
				break;
			case Mostrar_Conta:
				interface->MostrarConta();
				break;
			case Mudar_Conta:
				interface->MudarConta();
				break;
			case Excluir_Conta:
				interface->ExcluirConta();
				interface->Login();
				break;
			case Novo_Canal:
				interface->CreateCanal();
				break;
			case Mudar_Canal:
				interface->MudarCanal();
				break;
			case Deletar_Canal:
				interface->ExcluirCanal();
				break;
			case Videos:
				interface->ListarVideos();
				break;
			case Seus_Videos:
				interface->ListarSeusVideos();
				break;
			case Playlists:
				interface->Listarplaylists();
				break;
			case Mandar_Msgs:
				interface->MandarMsgs();
				break;
			case Checar_Msgs:
				interface->ChecarMsgs();
				break;
			case Audios:
				interface->ListarAudios();
				break;
			case Recomendacoes:
				interface->ListarRecomendacoes();
				break;
			case Sair:
				return 0;
		}
	}while(true);


	return 0;
}