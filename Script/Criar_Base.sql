--CREATE DATABASE DBProject;
--DROP DATABASE DBProject;
--select popular();

create table if not exists usuários(
	email varchar(200) primary key,
	nome_de_usuário varchar(200) not null,
	senha varchar(200) not null,
	data_de_nascimento date
);

create table if not exists mensagens(
	id serial primary key,
	texto varchar(1000) not null,
	data_de_publicação date not null,
	remetente text not null references usuários on delete cascade,
	autor text not null references usuários on delete cascade,
	foreign key (autor)
		references usuários(email) on update cascade,
	foreign key (remetente)
		references usuários(email) on update cascade
);

create table if not exists canais(
	url varchar(1000) primary key,
	nome varchar(200) not null,
	banner bytea not null,
	dono text not null unique references usuários on delete cascade,
	foreign key (dono)
		references usuários(email) on update cascade
);

create table if not exists recomendações(
	canal_dono text not null references canais on delete cascade,
	recomendação text not null references canais on delete cascade,
	comentário varchar(1000),
	primary key (canal_dono, recomendação),
	foreign key (canal_dono)
		references canais(url) on update cascade,
	foreign key (recomendação)
		references canais(url) on update cascade
);

create table if not exists áudios(
	id serial primary key,
	nome varchar(200) not null,
	conteúdo bytea not null
);

create table if not exists recursos_áudio(
	canal_dono text not null references canais on delete cascade,
	id_áudio int not null references áudios on delete cascade,
	primary key (canal_dono, id_áudio),
	foreign key (canal_dono)
		references canais(url) on update cascade,
	foreign key (id_áudio)
		references áudios(id) on update cascade
);

create table if not exists vídeos(
	url varchar(1000) primary key,
	título varchar(200) not null,
	thumbnail bytea not null,
	conteúdo bytea not null,
	data_de_criação date not null,
	privado bool not null,
	canal_dono text not null references canais on delete cascade,
	foreign key (canal_dono)
		references canais(url) on update cascade
);

create table if not exists legendas(
	id serial primary key,
	conteúdo bytea not null,
	língua varchar(200) not null,
	vídeo text not null references vídeos on delete cascade,
	foreign key (vídeo)
		references vídeos(url) on update cascade
);

create table if not exists playlists(
	id serial primary key,
	nome varchar(200) not null,
	usuário text not null references usuários on delete cascade,
	foreign key (usuário)
		references usuários(email)
);

create table if not exists vídeos_da_playlist(
	id_playlist int not null references playlists on delete cascade,
	vídeo_url text not null references vídeos on delete cascade,
	primary key (vídeo_url, id_playlist),
	foreign key (id_playlist)
		references playlists(id) on update cascade,
	foreign key (vídeo_url)
		references vídeos(url) on update cascade
);

create table if not exists comentários(
	id serial primary key,
	texto varchar(1000) not null,
	data_de_publicação date not null,
	resposta int references comentários on delete cascade,
	vídeo_url text not null references vídeos on delete cascade,
	autor text not null references usuários on delete cascade,
	foreign key (autor)
		references usuários(email) on update cascade,
	foreign key (vídeo_url)
		references vídeos(url) on update cascade,
	foreign key (resposta)
		references comentários(id) on update cascade
);

create or replace view view_vídeos_playlist
	as select p.nome, v.título, v.url, v.thumbnail, v.conteúdo
	from vídeos as v inner join vídeos_da_playlist as vp on v.url = vp.vídeo_url
	left join playlists as p on vp.id_playlist = p.id;

create or replace function Login(email text, senha text)
	returns bool as $$
	declare b_login bool;
	begin
		select (count(*) = 1) into b_login
		from public.usuários as u
		where u.email = $1 and u.senha = $2;
		return b_login;
	end
	$$ LANGUAGE plpgsql;


create or replace function Popular()
	returns void as $$
	declare result_audios áudios;
	declare id1 int;
	declare id2 int;
	declare id3 int;
	declare id4 int;
	declare id5 int;
	begin
		insert into usuários(email, nome_de_usuário, senha) values
		('user1@gmail.com', 'joao', '123'),
		('user2@gmail.com', 'pedro', '123'),
		('user3@gmail.com', 'maria', '123');
		insert into usuários(email, nome_de_usuário, senha, data_de_nascimento) values
		('user4@gmail.com', 'jose', '123', '2022-09-11'),
		('user5@gmail.com', 'clara', '123', '2022-09-11');
	
		insert into mensagens(texto, data_de_publicação, remetente, autor) values
		('oi', '2022-09-11', 'user2@gmail.com', 'user1@gmail.com'),
		('oi, joao', '2022-09-11', 'user1@gmail.com', 'user2@gmail.com'),
		('eu falo cmg msm', '2022-09-11', 'user3@gmail.com', 'user3@gmail.com'),
		('Não conta pro pedro, mas eu gosto, dele!', '2022-09-11', 'user4@gmail.com', 'user5@gmail.com'),
		('A clara ta tão na sua, cara...', '2022-09-11', 'user2@gmail.com', 'user4@gmail.com');
	
		insert into canais(url, nome, banner, dono) values
		('www.videosLegais.com/usr1_canal', 'canalDaHora', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Banners/banner1.jpg'), 'user1@gmail.com'),
		('www.videosLegais.com/usr2_canal', 'usr2_canal', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Banners/banner2.jpg'), 'user2@gmail.com'),
		('www.videosLegais.com/usr3_canal', 'canalMassa', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Banners/banner3.jpg'), 'user3@gmail.com'),
		('www.videosLegais.com/usr4_canal', 'canalDoJose', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Banners/banner4.jpg'), 'user4@gmail.com'),
		('www.videosLegais.com/usr5_canal', 'centralvideos', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Banners/banner5.jpg'), 'user5@gmail.com');
		
		insert into recomendações(canal_dono, recomendação) values
		('www.videosLegais.com/usr2_canal', 'www.videosLegais.com/usr1_canal'),
		('www.videosLegais.com/usr1_canal', 'www.videosLegais.com/usr2_canal'),
		('www.videosLegais.com/usr1_canal', 'www.videosLegais.com/usr3_canal'),
		('www.videosLegais.com/usr1_canal', 'www.videosLegais.com/usr4_canal'),
		('www.videosLegais.com/usr1_canal', 'www.videosLegais.com/usr5_canal');
	
		insert into áudios(nome, conteúdo) values
		('audio massa', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Audios/audio1.jpg')) returning id into id1;
		insert into áudios(nome, conteúdo) values
		('audio legal', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Audios/audio2.jpg')) returning id into id2;
		insert into áudios(nome, conteúdo) values
		('audio dahora', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Audios/audio3.jpg')) returning id into id3;
		insert into áudios(nome, conteúdo) values
		('super audio', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Audios/audio4.jpg')) returning id into id4;
		insert into áudios(nome, conteúdo) values
		('audio sem graça', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Audios/audio5.jpg')) returning id into id5;
	
		insert into recursos_áudio(canal_dono, id_áudio) values
		('www.videosLegais.com/usr1_canal', id1),
		('www.videosLegais.com/usr1_canal', id2),
		('www.videosLegais.com/usr1_canal', id3),
		('www.videosLegais.com/usr1_canal', id4),
		('www.videosLegais.com/usr2_canal', id5);

		insert into vídeos(url, título, thumbnail, conteúdo, data_de_criação, privado, canal_dono) values
		('www.videosLegais.com/video/video_do_porco?c=usr1_canal', 'vídeo do porco', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Thumbnails/thumbnail1.jpg'), bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Videos/video1.jpg'), '2022-09-11', false, 'www.videosLegais.com/usr1_canal'),
		('www.videosLegais.com/video/video_de_predio?c=usr2_canal', 'vídeo de predio', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Thumbnails/thumbnail2.jpg'), bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Videos/video2.jpg'), '2022-09-11', false, 'www.videosLegais.com/usr2_canal'),
		('www.videosLegais.com/video/porque_eu_nao_votei?c=usr3_canal', 'porque eu não votei?', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Thumbnails/thumbnail3.jpg'), bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Videos/video3.jpg'), '2022-09-11', true, 'www.videosLegais.com/usr3_canal'),
		('www.videosLegais.com/video/top_10_piadas(gone_sexual?)?c=usr4_canal', 'top 10 piadas(gone sexual?)', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Thumbnails/thumbnail4.jpg'), bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Videos/video4.jpg'), '2022-09-11', false, 'www.videosLegais.com/usr4_canal'),
		('www.videosLegais.com/video/video_de_musica?c=usr5_canal', 'vídeo de música', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Thumbnails/thumbnail5.jpg'), bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Videos/video5.jpg'), '2022-09-11', false, 'www.videosLegais.com/usr5_canal');
		
		insert into legendas(vídeo, conteúdo, língua) values
		('www.videosLegais.com/video/video_do_porco?c=usr1_canal', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Legendas/legenda1.jpg'), 'português'),
		('www.videosLegais.com/video/video_do_porco?c=usr1_canal', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Legendas/legenda2.jpg'), 'inglês'),
		('www.videosLegais.com/video/video_de_predio?c=usr2_canal', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Legendas/legenda3.jpg'), 'russo'),
		('www.videosLegais.com/video/video_do_porco?c=usr1_canal', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Legendas/legenda4.jpg'), 'russo'),
		('www.videosLegais.com/video/video_de_musica?c=usr5_canal', bytea('sf_Pastas_Compartilhadas/DB/Projeto/binarios/Legendas/legenda5.jpg'), 'português');
		
		insert into playlists(nome, usuário) values
		('melhores_videos', 'user1@gmail.com') returning id into id1;
		insert into playlists(nome, usuário) values
		('melhores_musicas', 'user1@gmail.com') returning id into id2;
		insert into playlists(nome, usuário) values
		('videos_favoritos', 'user2@gmail.com') returning id into id3;
		insert into playlists(nome, usuário) values
		('video_mais_lindo', 'user3@gmail.com') returning id into id4;
		insert into playlists(nome, usuário) values
		('video_engraçado', 'user4@gmail.com') returning id into id5;
	
		insert into vídeos_da_playlist(id_playlist, vídeo_url) values
		(id1, 'www.videosLegais.com/video/video_do_porco?c=usr1_canal'),
		(id2, 'www.videosLegais.com/video/video_de_musica?c=usr5_canal'),
		(id3, 'www.videosLegais.com/video/video_do_porco?c=usr1_canal'),
		(id4, 'www.videosLegais.com/video/video_do_porco?c=usr1_canal'),
		(id5, 'www.videosLegais.com/video/top_10_piadas(gone_sexual?)?c=usr4_canal');
	
		insert into comentários(texto, data_de_publicação, autor, vídeo_url) values
		('Que vídeo maneiro', '2022-09-11', 'user1@gmail.com', 'www.videosLegais.com/video/video_do_porco?c=usr1_canal'),
		('Que vídeo legal!!!', '2022-09-11', 'user2@gmail.com', 'www.videosLegais.com/video/video_do_porco?c=usr1_canal'),
		('Que vídeo lindo S2 S2 S2', '2022-09-11', 'user3@gmail.com', 'www.videosLegais.com/video/video_do_porco?c=usr1_canal'),
		('Não entendi porque tanta hype...', '2022-09-11', 'user4@gmail.com', 'www.videosLegais.com/video/video_do_porco?c=usr1_canal'),
		('Vídeo sem graça...', '2022-09-11', 'user4@gmail.com', 'www.videosLegais.com/video/video_do_porco?c=usr1_canal');
	end
	$$  LANGUAGE plpgsql;

