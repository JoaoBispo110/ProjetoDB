#ifndef PERSISTENCIA
#define PERSISTENCIA

	#include <pqxx/pqxx>

	class Persistencia{
		private:
		//Atributes:
			std::shared_ptr<pqxx::connection> m_connection;

		//Methods:
			Persistencia();

		public:
			Persistencia(Persistencia const&) = delete;
			void operator=(Persistencia const&)  = delete;
			~Persistencia() = default;

			static Persistencia& GetInstance();
			pqxx::result Comando(std::string comando);
			void Criar(std::string tabela, std::vector<std::string> campos, std::vector<std::string> valores, int* id = NULL);
			pqxx::result Consultar(std::string tabela, std::vector<std::string> campos, std::string clasula = "");
			pqxx::result Atualizar(std::string tabela, std::vector<std::string> campos, std::vector<std::string> valores, std::string clasula = "", std::string returns = "");
			void Deletar(std::string tabela, std::string clasula);
			bool Login(std::string email, std::string senha);
			bool UserTemCanal(std::string email);
			bool Cadastrar(std::string email, std::string senha, std::string nome, std::string data);
			bool AtualizarConta(std::string email, std::string nome, std::string senha, std::string data, std::string og_email);
			void DeletarConta(std::string email, std::string senha);
	};

#endif