#include "Model.h"
#include "func.h"

#define PI 3.14159265358979323846f  


const glm::mat4 WorldMatrix = glm::mat4(1.0f);


int WinWidth;
int WinHeight;


bool RotationMode;
bool CamMoved = false;
GLfloat CamSpeed = 0.1;
float objectX = 0;
float objectZ = 0;
bool flag = 0;
bool flag2 = 0;
float rad = 15.0f;

void processMouseInput(GLFWwindow* window, double xPos, double yPos);

glm::vec3 cameraFront;
glm::vec3 CamPosition = glm::vec3(0, 0, -2);
glm::vec3 CamTarget = glm::vec3(0,0,0);
glm::vec3 CamUp = glm::vec3(0, 1, 0);
GLfloat lastX = WinWidth / 2.0;
GLfloat lastY = WinHeight / 2.0;
bool firstMouse = true;

// Углы Эйлера
GLfloat yaw = 0.0f;
GLfloat pitch = 0.0f;
GLfloat fov = 45.0f;

int main() {
    srand(time(nullptr));

    glm::mat4 MMatr = WorldMatrix;
    glm::mat4 VMatr = WorldMatrix;
    glm::mat4 MMatr1 = WorldMatrix;
    glm::mat4 PMatr = WorldMatrix;

    GLFWwindow* window = InitAll(1024, 768, false);
    if (window == nullptr)
    {
        EndAll();
        return -1;
    }
    //Время запуска программы, нужно для анимации.
    double start_time = glfwGetTime();

    //Массивы для хранения атрибутов вершин
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_textures;
    std::vector< glm::vec3 > temp_normals;
    size_t size;
    float r, g, b;

    std::vector< glm::vec3 > temp_vertices1;
    std::vector< glm::vec2 > temp_textures1;
    std::vector< glm::vec3 > temp_normals1;
    size_t size1;

    std::vector< glm::vec3 > temp_vertices2;
    std::vector< glm::vec2 > temp_textures2;
    std::vector< glm::vec3 > temp_normals2;
    size_t size2;

    MMatr = WorldMatrix;


    //////////////////////////////потолок
    glm::vec3 points2[] = {
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f}
    };
    GLuint indices2[] = { 0, 1, 2, 3, 0, 2 };

    Model cube1(window, 2);
    std::vector< glm::vec2 > temp_textures3;

    temp_textures3.push_back({ 1.0, 1.0 });
    temp_textures3.push_back({ 0.0,1.0 });
    temp_textures3.push_back({ 0.0,0.0 });
    temp_textures3.push_back({ 1.0,0.0 });


  //  size = temp_vertices3.size();

    cube1.load_coords(points2, 4);
    cube1.load_indices(indices2, 6);
    cube1.load_texcoord(temp_textures3.data(), temp_textures3.size());
    cube1.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    cube1.load_shaders("texvs.glsl", "texfs.glsl");
    cube1.load_texture("pictures/top.jpg", "");

    /////////////пол

    glm::vec3 points3[] = {
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}
    };
    GLuint indices3[] = { 0, 1, 2, 3, 0, 2 };

    Model cube2(window,2);
    std::vector< glm::vec2 > temp_textures4;


    temp_textures4.push_back({ 1.0, 1.0 });
    temp_textures4.push_back({ 0.0,0.0 });

    temp_textures4.push_back({ 1.0,0.0 });
    temp_textures4.push_back({ 0.0,1.0 });

    cube2.load_coords(points3, 4);
    cube2.load_indices(indices3, 6);
    cube2.load_texcoord(temp_textures4.data(), temp_textures4.size());
    cube2.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    cube2.load_shaders("texvs.glsl", "texfs.glsl");
    cube2.load_texture("pictures/bottom.jpg", "");

    ///////////////////////////////// стена 1
        glm::vec3 points4[] = {
    {-1.0f, 1.0f, 1.0f}, ///1
    {-1.0f, 1.0f, -1.0f}, //2
    {-1.0f, -1.0f, -1.0f}, //3
    {-1.0f, -1.0f, 1.0f}
    };
    GLuint indices4[] = { 0, 1, 2, 3, 0, 2 };

    Model cube3(window,2);
    std::vector< glm::vec2 > temp_textures5;

    temp_textures5.push_back({ 1.0, 0.0 });
    temp_textures5.push_back({ 0.0, 0.0 });
    temp_textures5.push_back({ 0.0,1.0 });
    temp_textures5.push_back({ 1.0, 1.0 });
    size = temp_vertices.size();

    cube3.load_coords(points4, 4);
    cube3.load_indices(indices4, 6);
    cube3.load_texcoord(temp_textures5.data(), temp_textures5.size());
    cube3.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    cube3.load_shaders("texvs.glsl", "texfs.glsl");
    cube3.load_texture("pictures/wall1.jpg", "");
    /////////////////// стена 2

            glm::vec3 points5[] = {
    {-1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {-1.0f, -1.0f, 1.0f}
    };
    GLuint indices5[] = { 0, 1, 2, 3, 0, 2 };

    Model cube4(window,2);
    std::vector< glm::vec2 > temp_textures6;

    temp_textures6.push_back({ 0.0, 0.0 });
    temp_textures6.push_back({ 1.0,0.0 });

    temp_textures6.push_back({ 1.0, 1.0 });
    temp_textures6.push_back({ 0.0, 1.0 });


  //  size = temp_vertices.size();

    cube4.load_coords(points5, 4);
    cube4.load_indices(indices5, 6);
    cube4.load_texcoord(temp_textures6.data(), temp_textures6.size());
    cube4.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    cube4.load_shaders("texvs.glsl", "texfs.glsl");
    cube4.load_texture("pictures/wall2.jpg", "");

    ////////////////////// стена 3

                glm::vec3 points6[] = {
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f},
    {1.0f, -1.0f, 1.0f}
    };
    GLuint indices6[] = { 0, 1, 2, 3, 0, 2 };

    Model cube5(window,2);
    std::vector< glm::vec2 > temp_textures7;

    temp_textures7.push_back({ 0.0, 0.0 });
    temp_textures7.push_back({ 1.0,0.0 });

    temp_textures7.push_back({ 1.0, 1.0 });
    temp_textures7.push_back({ 0.0, 1.0 });
  //  size = temp_vertices.size();

    cube5.load_coords(points6, 4);
    cube5.load_indices(indices6, 6);
    cube5.load_texcoord(temp_textures7.data(), temp_textures7.size());
    cube5.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    cube5.load_shaders("texvs.glsl", "texfs.glsl");
    cube5.load_texture("pictures/wall3.jpg", "");


    ///////////// СТЕНА 4

                    glm::vec3 points7[] = {
    {-1.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}
    };
    GLuint indices7[] = { 0, 1, 2, 3, 0, 2 };

    Model cube6(window,2);
    std::vector< glm::vec2 > temp_textures8;

    temp_textures8.push_back({ 1.0, 0.0 });
    temp_textures8.push_back({ 0.0, 0.0 });
    temp_textures8.push_back({ 0.0,1.0 });
    temp_textures8.push_back({ 1.0, 1.0 });  //  size = temp_vertices.size();

    cube6.load_coords(points7, 4);
    cube6.load_indices(indices7, 6);
    cube6.load_texcoord(temp_textures8.data(), temp_textures8.size());
    cube6.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    cube6.load_shaders("texvs.glsl", "texfs.glsl");
    cube6.load_texture("pictures/wall4.jpg", "");

    //////////////////////////////




    loadOBJ("models/ii2.obj", temp_vertices, temp_textures, temp_normals);
    size = temp_vertices.size();
    Model main(window,2);
    //Загрузка данных модели
    main.load_coords(temp_vertices.data(), size);
    main.load_normals(temp_normals.data(), temp_normals.size());
    main.load_texcoord(temp_textures.data(), temp_textures.size());
    main.load_shaders("texvs.glsl", "texfs.glsl");
    main.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 32);
    //Капибары не отражают ничего!
    main.load_texture("pictures/grey5.jpeg", "");


    loadOBJ("models/floor1.obj", temp_vertices1, temp_textures1, temp_normals1);
    size1 = temp_vertices1.size();
    Model floor(window,2);
    //Загрузка данных модели
    floor.load_coords(temp_vertices1.data(), size1);
    floor.load_normals(temp_normals1.data(), temp_normals1.size());
    floor.load_texcoord(temp_textures1.data(), temp_textures1.size());
    floor.load_shaders("texvs.glsl", "texfs.glsl");
    floor.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    //Капибары не отражают ничего!
    floor.load_texture("pictures/grey4.jpeg", "");


    loadOBJ("models/rock.obj", temp_vertices2, temp_textures2, temp_normals2);
    size2 = temp_vertices2.size();
    Model rock(window,2);
    //Загрузка данных модели
    rock.load_coords(temp_vertices2.data(), size2);
    rock.load_normals(temp_normals2.data(), temp_normals2.size());
    rock.load_texcoord(temp_textures2.data(), temp_textures2.size());
    rock.load_shaders("texvs.glsl", "texfs.glsl");
    rock.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    //Капибары не отражают ничего!
    rock.load_texture("pictures/brown.jpg", "");



    std::vector< glm::vec3 > temp_vertices9;
    std::vector< glm::vec2 > temp_textures9;
    std::vector< glm::vec3 > temp_normals9;
    // std::vector< glm::vec3 > temp_colors1;
    // std::vector< GLuint > temp_indices1;
    size_t size9;

    loadOBJ("models/greenrock.obj", temp_vertices9, temp_textures9, temp_normals9);
    size9 = temp_vertices9.size();
    Model greenrock(window, 2);
    //Загрузка данных модели
    greenrock.load_coords(temp_vertices9.data(), size9);
    greenrock.load_normals(temp_normals9.data(), temp_normals9.size());
    greenrock.load_texcoord(temp_textures9.data(), temp_textures9.size());
    greenrock.load_shaders("texvs.glsl", "texfs.glsl");
    greenrock.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    //Капибары не отражают ничего!
    greenrock.load_texture("pictures/green.jpeg", "");



    std::vector< glm::vec3 > temp_vertices10;
    std::vector< glm::vec2 > temp_textures10;
    std::vector< glm::vec3 > temp_normals10;
    size_t size10;

    loadOBJ("models/crystals1.obj", temp_vertices10, temp_textures10, temp_normals10);
    size10 = temp_vertices10.size();
    Model crystals1(window, 2);
    crystals1.load_coords(temp_vertices10.data(), size10);
    crystals1.load_normals(temp_normals10.data(), temp_normals10.size());
    crystals1.load_texcoord(temp_textures10.data(), temp_textures10.size());
    crystals1.load_shaders("texvs.glsl", "texfs.glsl");
    crystals1.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    crystals1.load_texture("pictures/cr4.jpg","");

    std::vector< glm::vec3 > temp_vertices11;
    std::vector< glm::vec2 > temp_textures11;
    std::vector< glm::vec3 > temp_normals11;
    size_t size11;

    loadOBJ("models/crystals2.obj", temp_vertices11, temp_textures11, temp_normals11);
    size11 = temp_vertices11.size();
    Model crystals2(window, 2);
    crystals2.load_coords(temp_vertices11.data(), size11);
    crystals2.load_normals(temp_normals11.data(), temp_normals11.size());
    crystals2.load_texcoord(temp_textures11.data(), temp_textures11.size());
    crystals2.load_shaders("texvs.glsl", "texfs.glsl");
    crystals2.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    crystals2.load_texture("pictures/cr3.jpg", "");


    std::vector< glm::vec3 > temp_vertices12;
    std::vector< glm::vec2 > temp_textures12;
    std::vector< glm::vec3 > temp_normals12;
    size_t size12;

    loadOBJ("models/skeleton.obj", temp_vertices12, temp_textures12, temp_normals12);
    size12 = temp_vertices12.size();
    Model skeleton(window, 2);
    skeleton.load_coords(temp_vertices12.data(), size12);
    skeleton.load_normals(temp_normals12.data(), temp_normals12.size());
    skeleton.load_texcoord(temp_textures12.data(), temp_textures12.size());
    skeleton.load_shaders("texvs.glsl", "texfs.glsl");
    skeleton.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    skeleton.load_texture("pictures/grey4.jpeg", "");

    std::vector< glm::vec3 > temp_vertices13;
    std::vector< glm::vec2 > temp_textures13;
    std::vector< glm::vec3 > temp_normals13;
    size_t size13;

    loadOBJ("models/rocks.obj", temp_vertices13, temp_textures13, temp_normals13);
    size13 = temp_vertices13.size();
    Model rocks(window, 2);
    rocks.load_coords(temp_vertices13.data(), size13);
    rocks.load_normals(temp_normals13.data(), temp_normals13.size());
    rocks.load_texcoord(temp_textures13.data(), temp_textures13.size());
    rocks.load_shaders("texvs.glsl", "texfs.glsl");
    rocks.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    rocks.load_texture("pictures/grey5.jpeg", "");

    std::vector< glm::vec3 > temp_vertices14;
    std::vector< glm::vec2 > temp_textures14;
    std::vector< glm::vec3 > temp_normals14;
    size_t size14;

    loadOBJ("models/liana.obj", temp_vertices14, temp_textures14, temp_normals14);
    size14 = temp_vertices14.size();
    Model liana(window, 2);
    liana.load_coords(temp_vertices14.data(), size14);
    liana.load_normals(temp_normals14.data(), temp_normals14.size());
    liana.load_texcoord(temp_textures14.data(), temp_textures14.size());
    liana.load_shaders("texvs.glsl", "texfs.glsl");
    liana.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    liana.load_texture("pictures/green.jpeg", "");

    std::vector< glm::vec3 > temp_vertices15;
    std::vector< glm::vec2 > temp_textures15;
    std::vector< glm::vec3 > temp_normals15;
    size_t size15;

    loadOBJ("models/tree.obj", temp_vertices15, temp_textures15, temp_normals15);
    size15 = temp_vertices15.size();
    Model tree(window, 2);
    tree.load_coords(temp_vertices15.data(), size15);
    tree.load_normals(temp_normals15.data(), temp_normals15.size());
    tree.load_texcoord(temp_textures15.data(), temp_textures15.size());
    tree.load_shaders("texvs.glsl", "texfs.glsl");
    tree.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    tree.load_texture("pictures/brown2.jpeg", "");

    std::vector< glm::vec3 > temp_vertices16;
    std::vector< glm::vec2 > temp_textures16;
    std::vector< glm::vec3 > temp_normals16;
    size_t size16;

    loadOBJ("models/mushroom1.obj", temp_vertices16, temp_textures16, temp_normals16);
    size16 = temp_vertices16.size();
    Model mushroom1(window, 2);
    mushroom1.load_coords(temp_vertices16.data(), size16);
    mushroom1.load_normals(temp_normals16.data(), temp_normals16.size());
    mushroom1.load_texcoord(temp_textures16.data(), temp_textures16.size());
    mushroom1.load_shaders("texvs.glsl", "texfs.glsl");
    mushroom1.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    mushroom1.load_texture("pictures/blue.jpeg", "");



    std::vector< glm::vec3 > temp_vertices17;
    std::vector< glm::vec2 > temp_textures17;
    std::vector< glm::vec3 > temp_normals17;
    size_t size17;

    loadOBJ("models/mushroom2.obj", temp_vertices17, temp_textures17, temp_normals17);
    size17 = temp_vertices17.size();
    Model mushroom2(window, 2);
    mushroom2.load_coords(temp_vertices17.data(), size17);
    mushroom2.load_normals(temp_normals17.data(), temp_normals17.size());
    mushroom2.load_texcoord(temp_textures17.data(), temp_textures17.size());
    mushroom2.load_shaders("texvs.glsl", "texfs.glsl");
    mushroom2.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    mushroom2.load_texture("pictures/orange.jpeg", "");


    std::vector< glm::vec3 > temp_vertices18;
    std::vector< glm::vec2 > temp_textures18;
    std::vector< glm::vec3 > temp_normals18;
    size_t size18;

    loadOBJ("models/mushroom3.obj", temp_vertices18, temp_textures18, temp_normals18);
    size18 = temp_vertices18.size();
    Model mushroom3(window, 2);
    mushroom3.load_coords(temp_vertices18.data(), size18);
    mushroom3.load_normals(temp_normals18.data(), temp_normals18.size());
    mushroom3.load_texcoord(temp_textures18.data(), temp_textures18.size());
    mushroom3.load_shaders("texvs.glsl", "texfs.glsl");
    mushroom3.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    mushroom3.load_texture("pictures/mush4.jpg", "");




    std::vector< glm::vec3 > temp_vertices19;
    std::vector< glm::vec2 > temp_textures19;
    std::vector< glm::vec3 > temp_normals19;
    size_t size19;

    loadOBJ("models/mushroom4.obj", temp_vertices19, temp_textures19, temp_normals19);
    size19 = temp_vertices19.size();
    Model mushroom4(window, 2);
    mushroom4.load_coords(temp_vertices19.data(), size19);
    mushroom4.load_normals(temp_normals19.data(), temp_normals19.size());
    mushroom4.load_texcoord(temp_textures19.data(), temp_textures19.size());
    mushroom4.load_shaders("texvs.glsl", "texfs.glsl");
    mushroom4.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    mushroom4.load_texture("pictures/violet.jpeg", "");



    std::vector< glm::vec3 > temp_vertices20;
    std::vector< glm::vec2 > temp_textures20;
    std::vector< glm::vec3 > temp_normals20;
    size_t size20;

    loadOBJ("models/bird.obj", temp_vertices20, temp_textures20, temp_normals20);
    size20 = temp_vertices20.size();
    Model bird(window, 2);
    bird.load_coords(temp_vertices20.data(), size20);
    bird.load_normals(temp_normals20.data(), temp_normals20.size());
    bird.load_texcoord(temp_textures20.data(), temp_textures20.size());
    bird.load_shaders("texvs.glsl", "texfs.glsl");
    bird.setMaterial(glm::vec3(1), glm::vec3(1), glm::vec3(1), 32);
    bird.load_texture("pictures/grey.jpg", "");








    GLint maxLights;
    glGetIntegerv(GL_MAX_LIGHTS, &maxLights);

    cout << maxLights;



    //Параметры освещения сцены
    LightsInfo Lights;

    Lights.numPLights = 1;
    Lights.numSLights = 1;

    glm::vec3 lightPos = { 2.6,2.1,2.9 };
    glm::vec3 la = { 0.8f, 0.8f, 0.8f };
    glm::vec3 ld = { 0.3f, 0.3f, 0.3f };
    glm::vec3 ls = { 1,1,1 };


    DirLight lSource;
    lSource.ambient = la;
    lSource.diffuse = ld;
    lSource.specular = ls;
    lSource.direction = glm::vec3(0,-3, 0);
    Lights.dirLight = lSource;

    PointLight P;
    P.ambient = glm::vec3(0.7f, 0.0f, 0.7f);
    P.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    P.specular = glm::vec3(1, 1, 1);
    P.position = { -2.2,1.6,-0.35 };
    P.constant = 1;
    P.linear = 0.35;
    P.quadratic = 0.44;
    Lights.pointLights.push_back(P);


    SpotLight SP;
    //SP.ambient = glm::vec3(0.6, 0.6, 0.6);
    //SP.diffuse = glm::vec3(0.6, 1, 1);
    //SP.specular = glm::vec3(1, 1, 1);
    //SP.position = glm::vec3(0, 3, 0);
    //SP.direction = glm::vec3(0.5, 1, 1);
    //SP.cutOff = glm::cos(glm::radians(12.5f));
    //SP.outerCutOff = glm::cos(glm::radians(15.0f));

    //SP.constant = 1;
    //SP.linear = 0.009;
    //SP.quadratic = 0.0032;
    Lights.spotLights.push_back(SP);

    
    
    PointLight P1;
    P1.ambient = glm::vec3(0.0f, 1.0f, 0.0f);
    //P1.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    //P1.specular = glm::vec3(1, 1, 1);
    //P1.position = { 4,3,5 };
    //P1.constant = 1;
    //P1.linear = 0.0014;
    //P1.quadratic = 0.000007;
    Lights.pointLights.push_back(P1);

    P.ambient = glm::vec3(0.0f, 0.4f, 0.4f);
    //P.diffuse = glm::vec3(0.9f, 0.1f, 0.4f);
    //P.specular = glm::vec3(1, 1, 1);
    //P.position = { -1, -3, -1 };
    //P.constant = 1;
    //P.linear = 0.09;
    //P.quadratic = 0.032;
    Lights.pointLights.push_back(P);



    //Матрицу проецирования можно задать сразу же, менять её не надо будет
    PMatr = glm::perspective(
        glm::radians(67.0f), // Угол обзора
        (float)WinWidth / WinHeight,       // Соотношение сторон
        0.01f,              // Ближняя плоскость отсечения
        10000.0f             // Дальняя плоскость отсечения
    );

    //Теперь начальные значения матрицы вида
    
    VMatr = glm::lookAt(CamPosition, CamTarget, CamUp);

    //Цвет фона
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    float rotation = 0;

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, processMouseInput);

    //И так как речь о 3d важно не забыть про буфер глубины (попробуйте убрать его)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);



    //Теперь рисование
    while (!glfwWindowShouldClose(window)) {

        double elapsed = glfwGetTime() - start_time;
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (CamMoved)
        {
            VMatr = WorldMatrix;
            VMatr = glm::lookAt(CamPosition, CamTarget, CamUp);
            CamMoved = false;
        }

        if (RotationMode)
            rotation = (float)elapsed;
        else
            rotation = -(float)elapsed;

        VMatr = glm::lookAt(CamPosition, CamTarget, CamUp);

        MMatr = WorldMatrix;
        MMatr = glm::scale(MMatr,glm::vec3(10.0,10.0,10.0));
        cube1.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        cube2.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        cube3.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        cube4.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        cube5.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        cube6.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        MMatr = WorldMatrix;
        main.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        floor.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        rock.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        MMatr = glm::scale(MMatr, glm::vec3(1.05, 1.05, 1.05));
        MMatr = glm::translate(MMatr,glm::vec3(0,-0.25,0));
        greenrock.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        MMatr = WorldMatrix;
        crystals1.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        crystals2.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        skeleton.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        rocks.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);


        MMatr = glm::rotate(MMatr, glm::radians(rad), glm::vec3(0.0, 0.0, 1.0));

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_T)) {
            flag2 = !flag2;
        }
        if (flag2 && rad > 0.0f) {
                rad -= 0.008f;
        }
        if (!flag2 && rad <= 15.0f) {
            rad += 0.008f;
        }
        liana.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        
        MMatr = WorldMatrix;


        mushroom1.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        mushroom2.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        mushroom3.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        mushroom4.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        if (CamPosition.x >= -1.5 && CamPosition.x <= 1.9 &&
            CamPosition.z >= -5.9 && CamPosition.z <= -3.0) {
            if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E))
            {
                flag = !flag;
            }
            if (flag) {
                if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W) && objectZ >= -0.024)
                {
                    objectZ -= 0.001f;
                    MMatr1 = glm::translate(MMatr, glm::vec3(objectX, 0.0, objectZ));
                }
                if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S) && objectZ <= 0.03)
                {
                    objectZ += 0.001f;
                    MMatr1 = glm::translate(MMatr, glm::vec3(objectX, 0.0, objectZ));
                }
                if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D) && objectX <= 0.071)
                {
                    objectX += 0.001f;
                    MMatr1 = glm::translate(MMatr, glm::vec3(objectX, 0.0, objectZ));
                }
                if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A) && objectX >= -0.725)
                {
                    objectX -= 0.001f;
                    MMatr1 = glm::translate(MMatr, glm::vec3(objectX, 0.0, objectZ));
                }

            }
        }
        tree.render(MMatr1, VMatr, PMatr, Lights, GL_TRIANGLES);

        MMatr = WorldMatrix;
            if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_R))
            {
                 MMatr = glm::rotate(MMatr,  -rotation, glm::vec3(0.0, 1.0, 0.0));
            }
            else {
                 MMatr = glm::rotate(MMatr,   rotation, glm::vec3(0.0, 1.0, 0.0));
            }

        bird.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        glfwPollEvents();
        glfwSwapBuffers(window);
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);
        }

    }

    return 0;
}

void processMouseInput(GLFWwindow* window, double xPos, double yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    const GLfloat sensitivity = 0.05f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 cameraFront = glm::normalize(front);

    CamTarget = CamPosition + cameraFront;
}