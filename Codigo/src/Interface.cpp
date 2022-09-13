#include <iostream>
#include <vector>
#include <string>
#include "Interface.h"

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;
using std::vector;
using std::exception;

Interface::Interface(): m_persistencia(&Persistencia::GetInstance()), m_user_email(""){}

Interface& Interface::GetInstance(){
	static Interface instancia;

	return instancia;
}

void Interface::Login(){
	string email;
	string senha;
	string log_ou_cad;

	do{
		cout << "Pressione Enter para continuar..." << endl;
		getchar();
		system("clear");

		cout << "'Esc': to exit" << endl;
		cout << "Seu email:" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, email);
		if(email.find(27) != -1){
			exit(-1);
		}

		cout << "Sua senha:" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, senha);
		if(senha.find(27) != -1){
			exit(-1);
		}

		cout << "Quer se (C)adastrar ou (L)oggar??" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, log_ou_cad);
		for (auto & c: log_ou_cad) c = toupper(c);

		if(log_ou_cad.find(27) != -1){
			exit(-1);
		}
		else if((log_ou_cad == "C") || (log_ou_cad == "CADASTRAR")){
			string nome;
			string data;
			bool se_data = false;

			cout << "Seu nome de usuario:" << endl;
			cout << "> ";
			cout.flush();
			getline(cin, nome);
			if(nome.find(27) != -1){
				exit(-1);
			}

			cout << "Quer incluir data de aniversario?" << endl;
			cout.flush();
			getline(cin, data);
			for (auto & c: data) c = toupper(c);

			if(data.find(27) != -1){
				exit(-1);
			}
			else if((data == "S") || (data == "SIM")){
				cout << "Sua data de aniversario (aaaa-mm-dd):" << endl;
				cout << "> ";
				cout.flush();
				getline(cin, data);
				if(data.find(27) != -1){
					exit(-1);
				}
			}
			else{
				data = "";
			}
			if(m_persistencia->Cadastrar(email, senha, nome, data)){
				m_user_email = email;
				m_se_tem_canal = false;
				return;
			}
		}
		else if((log_ou_cad == "L") || (log_ou_cad == "LOGGAR")){
			if(m_persistencia->Login(email, senha)){
				m_user_email = email;
				m_se_tem_canal = m_persistencia->UserTemCanal(email);
				return;
			}
		}

	}while(true);
}

Options Interface::Menu(){
	string input;

	do{
		cout << "Pressione Enter para continuar..." << endl;
		getchar();
		system("clear");

		cout << "Bem vindo: " << m_user_email << endl;
		cout << "'Esc': to exit" << endl;
		cout << "(L)ogOff" << endl;
//		cout << "(M)andar Msgs" << endl;
//		cout << "(C)hecar Msgs" << endl;
		cout << "(U)pdate Conta" << endl;
		cout << "(E)xcluir Conta" << endl;
		if(!m_se_tem_canal){
			cout << "(N)ovo Canal" << endl;
		}
		else if(m_se_tem_canal > 0){
//			cout << "(V)ideos" << endl;
//			cout << "(S)eus Videos" << endl;
//			cout << "(P)laylists" << endl;
//			cout << "(A)udios" << endl;
//			cout << "(R)ecomendacoes" << endl;
			cout << "(MC) mudar canal" << endl;
			cout << "(D)eletar Canal" << endl;
		}
		cout << "> ";
		cout.flush();
		getline(cin, input);
		for (auto & c: input) c = toupper(c);

		if(input.find(27) != -1){
			return Sair;
		}
		else if((input == "L") || (input == "LOGOFF")){
			return Log_Off;
		}
		else if((input == "M") || (input == "MANDAR MSGS")){
			return Mandar_Msgs;
		}
		else if((input == "C") || (input == "CHECAR MSGS")){
			return Checar_Msgs;
		}
		else if((input == "U") || (input == "UPDATE CONTA")){
			return Mudar_Conta;
		}
		else if((input == "E") || (input == "EXCLUIR CONTA")){
			return Excluir_Conta;
		}
		if(!m_se_tem_canal){
			if((input == "N") || (input == "NOVO CANAL")){
				return Novo_Canal;
			}
		}
		else{
			if((input == "V") || (input == "VIDEOS")){
				return Videos;
			}
			else if((input == "S") || (input == "SEUS VIDEOS")){
				return Seus_Videos;
			}
			else if((input == "P") || (input == "PLAYLISTS")){
				return Playlists;
			}
			else if((input == "A") || (input == "AUDIOS")){
				return Audios;
			}
			else if((input == "R") || (input == "RECOMENDCOES")){
				return Recomendacoes;
			}
			else if((input == "MC") || (input == "MUDAR CANAL")){
				return Mudar_Canal;
			}
			else if((input == "D") || (input == "DELETAR CANAL")){
				return Deletar_Canal;
			}
		}

	}while(true);

	return Sair;
}

void Interface::MudarConta(){
	string nome = "";
	string senha = "";
	string data = "";
	string email = "";
	string se_sim = "";

	do{
		cout << "Pressione Enter para continuar..." << endl;
		getchar();
		system("clear");

		cout << "'Esc': to exit" << endl;
		cout << "Quer mudar seu nome de usuário?" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, se_sim);
		for (auto & c: se_sim) c = toupper(c);


		if(se_sim.find(27) != -1){
			return;
		}
		else if((se_sim == "S") || (se_sim == "SIM")){
			cout << "Seu novo nome de usuário:" << endl;
			cout << "> ";
			cout.flush();
			getline(cin, nome);
			if(nome.find(27) != -1){
				return;
			}
			else{
				break;
			}
		}
		else if((se_sim == "N") || (se_sim == "NAO")){
			break;
		}
	}while(true);

	do{
		cout << "Pressione Enter para continuar..." << endl;
		getchar();
		system("clear");

		cout << "'Esc': to exit" << endl;
		cout << "Quer mudar sua senha?" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, se_sim);
		for (auto & c: se_sim) c = toupper(c);

		if(se_sim.find(27) != -1){
			return;
		}
		else if((se_sim == "S") || (se_sim == "SIM")){
			cout << "Confirme sua antiga senha, por favor:" << endl;
			cout << "> ";
			cout.flush();
			getline(cin, senha);
			if(senha.find(27) != -1){
				return;
			}
			if(!m_persistencia->Login(m_user_email, senha)){
				senha = "";
				continue;
			}

			cout << "Sua nova senha:" << endl;
			cout << "> ";
			cout.flush();
			getline(cin, senha);
			if(senha.find(27) != -1){
				return;
			}
			else{
				break;
			}
		}
		else if((se_sim == "N") || (se_sim == "NAO")){
			break;
		}
	}while(true);

	do{
		cout << "Pressione Enter para continuar..." << endl;
		getchar();
		system("clear");

		cout << "'Esc': to exit" << endl;
		cout << "Quer mudar sua data de nascimento?" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, se_sim);
		for (auto & c: se_sim) c = toupper(c);

		if(se_sim.find(27) != -1){
			return;
		}
		else if((se_sim == "S") || (se_sim == "SIM")){
			cout << "Sua nova data de nascimento (aaaa-mm-dd):" << endl;
			cout << "> ";
			cout.flush();
			getline(cin, data);
			if(data.find(27) != -1){
				return;
			}
			else{
				break;
			}
		}
		else if((se_sim == "N") || (se_sim == "NAO")){
			break;
		}
	}while(true);

	do{
		cout << "Pressione Enter para continuar..." << endl;
		getchar();
		system("clear");

		cout << "'Esc': to exit" << endl;
		cout << "Quer mudar seu email?" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, se_sim);
		for (auto & c: se_sim) c = toupper(c);

		if(se_sim.find(27) != -1){
			return;
		}
		else if((se_sim == "S") || (se_sim == "SIM")){
			cout << "Sua novo email:" << endl;
			cout << "> ";
			cout.flush();
			getline(cin, email);
			if(email.find(27) != -1){
				return;
			}
			else{
				break;
			}
		}
		else if((se_sim == "N") || (se_sim == "NAO")){
			break;
		}
	}while(true);

	if(m_persistencia->AtualizarConta(email, nome, senha, data, m_user_email)){
		if(email != ""){
			m_user_email = email;
		}
	}
}

void Interface::ExcluirConta(){
	string se_sim;
	string senha;

	do{
		cout << "Pressione Enter para continuar..." << endl;
		getchar();
		system("clear");

		cout << "'Esc': to exit" << endl;
		cout << "Tem certeza sobre deletar sua conta? (Isso eh irreversivel!!!)" << endl;
		cout << "> ";
		cout.flush();
		getline(cin, se_sim);


		if(se_sim.find(27) != -1){
			break;
		}
		else if((se_sim == "S") || (se_sim == "SIM")){
			cout << "Confirme sua antiga senha, por favor:" << endl;
			cout << "> ";
			cout.flush();
			getline(cin, senha);
			if(senha.find(27) != -1){
				break;
			}
			
			m_persistencia->DeletarConta(m_user_email, senha);
			m_user_email = "";
			break;
		}
		else if((se_sim == "N") || (se_sim == "NAO")){
			break;
		}
	}while(true);
}

void Interface::CreateCanal(){

}

void Interface::MudarCanal(){

}

void Interface::ExcluirCanal(){

}

void Interface::ListarVideos(){

}

void Interface::ListarSeusVideos(){

}

void Interface::Listarplaylists(){

}

void Interface::MandarMsgs(){

}

void Interface::ChecarMsgs(){

}

void Interface::ListarAudios(){

}

void Interface::ListarRecomendacoes(){

}
