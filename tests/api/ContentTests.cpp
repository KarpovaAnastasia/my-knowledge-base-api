#include <gtest/gtest.h>
#include "kb/api/stubs/StubPageService.h"
#include "kb/api/stubs/StubProjectService.h"

using namespace kb::api::stubs;

// Тест 1: Создание страницы 
TEST(PageTest, CreatePage) {
    StubPageService pageService;
    auto page = pageService.createPage("Тестовая страница", "Какой-то контент");

    ASSERT_FALSE(page.id.empty());
    EXPECT_EQ(page.title, "Тестовая страница");
    EXPECT_EQ(page.content, "Какой-то контент");
    EXPECT_EQ(page.version, 1);
}

// Тест 2: Получение существующей страницы
TEST(PageTest, GetExistingPage) {
    StubPageService pageService;
    auto page = pageService.getPage("page-1");

    ASSERT_TRUE(page.has_value());
    EXPECT_EQ(page->id, "page-1");
}

// Тест 3: Получение несуществующей страницы
TEST(PageTest, GetNonExistentPage) {
    StubPageService pageService;
    auto page = pageService.getPage("not-found");

    ASSERT_FALSE(page.has_value()); // Должно вернуться пустое значение
}


// Тест 4: Создание проекта
TEST(ProjectTest, CreateProject) {
    StubProjectService projectService;
    auto project = projectService.createProject("Мой проект", "Описание", "file-123", "test.pdf");

    ASSERT_FALSE(project.id.empty());
    EXPECT_EQ(project.name, "Мой проект");
    EXPECT_EQ(project.description, "Описание");
    EXPECT_EQ(project.attachmentId, "file-123");
    EXPECT_EQ(project.fileName, "test.pdf");
}

// Тест 5: Получение существующего проекта
TEST(ProjectTest, GetExistingProject) {
    StubProjectService projectService;
    auto project = projectService.getProject("project-1");

    ASSERT_TRUE(project.has_value());
    EXPECT_EQ(project->id, "project-1");
}

// Тест 6: Получение несуществующего проекта
TEST(ProjectTest, GetNonExistentProject) {
    StubProjectService projectService;
    auto project = projectService.getProject("not-found");

    ASSERT_FALSE(project.has_value());
}