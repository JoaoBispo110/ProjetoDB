#include <iostream>
#include <vector>
#include <string>
#include "Persistencia.h"

#define DEBUG true

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::exception;

Persistencia::Persistencia(){
	string options = "host=localhost port=5432 dbname=dbproject user=joao password=joao456123";

	try{
		m_connection.reset(new pqxx::connection(options));
	}
	catch(exception const &e){
		cerr << e.what() << endl;

	    return;
	}

	cout << "Conexao estabelecida com sucesso" << endl;
}

Persistencia& Persistencia::GetInstance(){
	static Persistencia instancia;

	return instancia;
}

pqxx::result Persistencia::Comando(std::string comando){
	pqxx::result resultado;

	if(DEBUG){
		cout << comando << endl;
	}

	try{
		pqxx::work trabalhador(*m_connection);
		resultado = trabalhador.exec(comando);
		trabalhador.commit();
	}
	catch(exception const &e){
		cerr << e.what() << endl;

	    throw e;
	}

	return resultado;
}

void Persistencia::Criar(string tabela, vector<string> campos, vector<string> valores, int* id){
	pqxx::result resultado;
	string comando("insert into " + tabela + "(");

	if(campos.size() != valores.size()){
		cerr << "Erro numero de campos e valores eh diferente" << endl;
		throw "Erro numero de campos e valores eh diferente";
	}

	for(auto it = campos.begin(); it != campos.end(); it++){
		if( it != campos.begin()){
			comando += ", ";
		}
		comando += *it;
	}

	comando += ") values ('";

	for(auto it = valores.begin(); it != valores.end(); it++){
		if( it != valores.begin()){
			comando += "', '";
		}
		comando += *it;
	}

	comando += "')";

	if(id != NULL){
		comando += " returning id";
	}

	comando += ";";
	try{
		resultado = Comando(comando);
	}
	catch(exception const &e){
	    throw e;
	}

	if(id != NULL){
		*id = resultado[0][0].as<int>();
	}
}

pqxx::result Persistencia::Consultar(string tabela, vector<string> campos, string clasula){
	pqxx::result resultado;
	string comando("select ");

	for(auto it = campos.begin(); it != campos.end(); it++){
		if( it != campos.begin()){
			comando += ", ";
		}
		comando += *it;
	}
	comando += " from " + tabela;
	if(clasula != ""){
		comando += " where " + clasula;
	}
	comando += ";";

	try{
		resultado = Comando(comando);
	}
	catch(exception const &e){
		throw e;
	}

	return resultado;
}

pqxx::result Persistencia::Atualizar(string tabela, vector<string> campos, vector<string> valores, string clasula, string returns){
	pqxx::result resultado;
	string comando("update " + tabela + " set ");

	if(campos.size() != valores.size()){
		cerr << "Erro numero de campos e valores eh diferente" << endl;
		throw "Erro numero de campos e valores eh diferente";
	}

	for(long unsigned int i = 0; i < campos.size(); i++){
		if( i != 0){
			comando += ", ";
		}
		comando += campos[i] + "='" + valores[i] + "'";
	}
	if(clasula != ""){
		comando += " where " + clasula;
	}
	if(returns != ""){
		comando += " returning " + returns;
	}
	comando += ";";

	try{
		resultado = Comando(comando);
	}
	catch(exception const &e){
		throw e;
	}

	return resultado;
}

void Persistencia::Deletar(string tabela, string clasula){
	string comando("delete from " + tabela + " where " + clasula + ";");

	try{
		Comando(comando);
	}
	catch(exception const &e){
		throw e;
	}

	return;
}

bool Persistencia::Login(string email, string senha){
	string comando;
	pqxx::result resultado;

	comando = "select Login('" + email + "', '" + senha + "');";
	try{
		resultado = Comando(comando);
	}
	catch(exception const &e){
		return false;
	}

	return resultado[0][0].as<bool>();
}

bool Persistencia::UserTemCanal(string email){
	vector<string> campos = {"count(*)"};
	string tabela("public.usuários as u inner join public.canais as c on c.dono = u.email");
	string clasula("u.email = '" + email + "'");
	pqxx::result resultado;

	try{
		resultado = Consultar(tabela, campos, clasula);
	}
	catch(exception const &e){
		return -1;
	}

	if(resultado[0][0].as<int>() == 1){
		return true;
	}
	else{
		return false;
	}
}

bool Persistencia::Cadastrar(string email, string senha, string nome, string data){
	vector<string> campos = {"email", "senha", "nome_de_usuário"};
	vector<string> valores = {email, senha, nome};
	string tabela("public.usuários");

	if(data != ""){
		campos.push_back("data_de_nascimento");
		valores.push_back(data);
	}

	try{
		Criar(tabela, campos, valores);
	}
	catch(exception const &e){
		return false;
	}

	return true;
}

bool Persistencia::AtualizarConta(string email, string nome, string senha, string data, string og_email){
	vector<string> campos;
	vector<string> valores;
	string tabela("public.usuários");
	string clasula("email ='" + og_email + "'");

	if(email != ""){
		campos.push_back("email");
		valores.push_back(email);
	}
	if(nome != ""){
		campos.push_back("nome_de_usuário");
		valores.push_back(nome);
	}
	if(senha != ""){
		campos.push_back("senha");
		valores.push_back(senha);
	}
	if(data != ""){
		campos.push_back("data_de_nascimento");
		valores.push_back(data);
	}

	if(campos.size() == 0){
		cout << "Tentou atualizar, mas nao selecionou nenhum campo para a atualizacao" << endl;
		return true;
	}

	try{
		Atualizar(tabela, campos, valores, clasula);
	}
	catch(exception const &e){
		return false;
	}

	return true;
}

void Persistencia::DeletarConta(string email, string senha){
	string tabela("public.usuários");
	string clasula("email = '" + email + "' and senha = '" + senha + "'");

	try{
		Deletar(tabela, clasula);
	}
	catch(exception const &e){}
}