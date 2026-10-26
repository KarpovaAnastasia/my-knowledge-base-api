# my-knowledge-base-api
добавила новое:
AuthController.h / AuthController.cpp  принимают запросы на вход (/login), выход (/logout) и получение профиля (/users/me)
AuthHelper.h / AuthHelper.cpp  проверяют наличие и правильность токена (Bearer) в заголовках запросов
StubUserService.h / StubUserService.cpp  имитируют проверку логина и пароля пользователя
StubSessionService.h / StubSessionService.cpp создают, хранят в памяти и проверяют сессии (токены)
ProjectController.cpp добавлена проверка токена для защиты от неавторизованного доступа

