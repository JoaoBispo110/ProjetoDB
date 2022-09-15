#ifndef INTERFACE
#define INTERFACE

	#include "Persistencia.h"

	enum Options{
		Log_Off,
		Mostrar_Conta,
		Mudar_Conta,
		Excluir_Conta,
		Novo_Canal,
		Mudar_Canal,
		Deletar_Canal,
		Videos,
		Seus_Videos,
		Playlists,
		Mandar_Msgs,
		Checar_Msgs,
		Audios,
		Recomendacoes,
		Sair
	};

	class Interface{
		private:
		//Atributes:
			bool m_se_tem_canal;
			std::string m_user_email;
			Persistencia* m_persistencia;

		//Methods:
			Interface();

		public:
			Interface(Interface const&) = delete;
			void operator=(Interface const&)  = delete;
			~Interface() = default;

			static Interface& GetInstance();
			void Login();
			Options Menu();
			void MostrarConta();
			void MudarConta();
			void ExcluirConta();
			void CreateCanal();
			void MudarCanal();
			void ExcluirCanal();
			void ListarVideos();
			void ListarSeusVideos();
			void Listarplaylists();
			void ListarSeusPlaylists();
			void MandarMsgs();
			void ChecarMsgs();
			void ListarAudios();
			void ListarRecomendacoes();
			
	};

#endif