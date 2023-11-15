#include "func.h"
#include "globals.h"


string LoadShader(const char* filename)
{
    string res;
    ifstream file(filename, ios::in);
    if (file.is_open()) {
        std::stringstream sstr; // ����� ��� ������
        sstr << file.rdbuf(); // ��������� ����
        res = sstr.str();   //�������� ������ �� ������
        file.close();       //��������� ����
    }
    return res;
}

GLFWwindow* InitAll(int w, int h, bool Fullscreen)
{
    //� ���������� ���������� ��������� ������� ����
    WinWidth = w;
    WinHeight = h;

    //������ ���������� ��� �������� ID ����
    GLFWwindow* window = nullptr;

    //����������� GLFW
    if (!glfwInit()) {
        cerr << "ERROR: could not start GLFW3\n";
        exit(-1);
    }

    // ��� ��� MacOS
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/


    //� ����������� �� ������ ������ �������� ���� � ���������� Capybara OpenGL
    if (Fullscreen)
    {

        GLFWmonitor* mon = glfwGetPrimaryMonitor();
        const GLFWvidmode* vmode = glfwGetVideoMode(mon);
        WinWidth = vmode->width;
        WinHeight = vmode->height;
        window = glfwCreateWindow(WinWidth, WinHeight, "Capybara OpenGL", mon, NULL);

    }
    else
        window = glfwCreateWindow(WinWidth, WinHeight, "Capybara OpenGL", NULL, NULL);

    //������������� ������� ��� ��������� �������
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);

    //������������ �������� ����
    glfwMakeContextCurrent(window);

    //����������� �������� �� ��������� ������ OpenGL
    glewExperimental = GL_TRUE;

    //����������� ������� OpenGL
    if (glewInit() != GLEW_OK) {
        cerr << "ERROR: could not start GLEW\n";
        return nullptr;
    }

    //���� ����� �� ���� - ���������� ����
    return window;
}

void EndAll()
{
    //������ ���������� GLFW
    //���� �� ����� �������� ������� ������ ���� ����� �����
    glfwTerminate();
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    //������ ������ ���������� ����������
    WinWidth = width;
    WinHeight = height;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   
    if (!flag) {
        if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
        {
            glm::vec3 cameraDirection = glm::normalize(CamTarget - CamPosition);
            CamPosition += CamSpeed * cameraDirection;
            CamTarget += CamSpeed * cameraDirection;
            CamMoved = true;
            cout << CamPosition.x << " x|" << CamPosition.y << " y|" << CamPosition.z << " z|" << endl;
        }
        if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
        {
            glm::vec3 cameraDirection = glm::normalize(CamTarget - CamPosition);
            CamPosition -= CamSpeed * cameraDirection;
            CamTarget -= CamSpeed * cameraDirection;
            CamMoved = true;
        }
        if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
        {
            glm::vec3 cameraRight = glm::normalize(glm::cross(CamUp, CamTarget - CamPosition));
            CamPosition -= CamSpeed * cameraRight;
            CamTarget -= CamSpeed * cameraRight;
            CamMoved = true;
        }
        if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
        {
            glm::vec3 cameraRight = glm::normalize(glm::cross(CamUp, CamTarget - CamPosition));
            CamPosition += CamSpeed * cameraRight;
            CamTarget += CamSpeed * cameraRight;
            CamMoved = true;
        }
    }
}



//bool loadOBJ(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals)
//{
//    //��������� ������� ��� �������� �������� � �������� �� �����
//    std::vector< unsigned int > vertexIndices, vtIndices, normalIndices;
//    std::vector< glm::vec3 > temp_vertices;
//    std::vector< glm::vec2 > temp_textures;
//    std::vector< glm::vec3 > temp_normals;
//
//    //������ ��� �������� ������� �� �����
//    string buf;
//    //�����, �������� ���������� �����
//    std::stringstream sstr;
//    //���������� ��� ���������� ������ � ����������� ������ ������ � �����
//    bool cont = false;
//
//    //���������� �����
//    ifstream file(path, ios::in);
//    if (file.is_open()) {
//        sstr << file.rdbuf();
//        file.close();
//    }
//    else
//        return false;
//
//    //������� �������� ��������
//    outNormals.clear();
//    outVertices.clear();
//    outTextures.clear();
//
//    //������� ������� ����� �� �����
//    while (cont || sstr >> buf) {
//        cont = false;
//
//        //��������� ���������
//        if (buf == "v") {
//            glm::vec3 vertex;
//            sstr >> vertex.x;
//            sstr >> vertex.y;
//            sstr >> vertex.z;
//            temp_vertices.push_back(vertex);
//        }
//        //��������� ���������� ���������
//        else if (buf == "vt") {
//            glm::vec2 texture;
//            sstr >> texture.x;
//            sstr >> texture.y;
//            temp_textures.push_back(texture);
//        }
//        //��������� ��������
//        else if (buf == "vn") {
//            glm::vec3 normal;
//            sstr >> normal.x;
//            sstr >> normal.y;
//            sstr >> normal.z;
//            temp_normals.push_back(normal);
//        }
//        //��������� ������
//        else if (buf == "f") {
//            //��������� ������� ��� �������� ���������� � �����
//            vector<string> vertexes;
//            vector<int> vertindexes;
//            while (!cont)
//            {
//                //����������� �����
//                sstr >> buf;
//                //���� ����� �������� ������ � ������� - ��� ������������ � ������
//                if (buf.find('/') != string::npos)
//                    vertexes.push_back(buf);
//                //���� ����� - ������ ��������� ������, �� ����������� � ���������� ��������� �����
//                else
//                {
//                    //��� ������ �� ���������� ������ ������������ ������� ������
//                    for (string vert : vertexes)
//                    {
//                        std::replace(vert.begin(), vert.end(), '/', ' ');
//                        std::stringstream tmpstream(vert);
//                        int v, vt, n;
//                        tmpstream >> v;
//                        tmpstream >> vt;
//                        tmpstream >> n;
//                        //������� ��������� � ��������� ������
//                        vertindexes.push_back(v);
//                        vertindexes.push_back(vt);
//                        vertindexes.push_back(n);
//                    }
//                    //������ ��� ������� ��������� �������� ��������
//                    for (int i = 0; i < 3; i++)
//                    {
//                        vertexIndices.push_back(vertindexes[i * 3 + 0]);
//                        vtIndices.push_back(vertindexes[i * 3 + 1]);
//                        normalIndices.push_back(vertindexes[i * 3 + 2]);
//                    }
//                    //������ ������� - ���� ��� �������� �������, ���� � �� �������
//                    //�� ���� ������������� �� ����� ������������� � ����� �������������
//                    size_t tmpsize = vertexes.size();
//                    if (tmpsize > 3)
//                    {
//                        //��� ������ �� ������ ����������� ��� �������, ���������� �����������
//                        for (int i = 3; i < tmpsize; i++)
//                        {
//                            vertexIndices.push_back(vertindexes[0]);
//                            vtIndices.push_back(vertindexes[1]);
//                            normalIndices.push_back(vertindexes[2]);
//                            vertexIndices.push_back(vertindexes[(i - 1) * 3 + 0]);
//                            vtIndices.push_back(vertindexes[(i - 1) * 3 + 1]);
//                            normalIndices.push_back(vertindexes[(i - 1) * 3 + 2]);
//                            vertexIndices.push_back(vertindexes[i * 3 + 0]);
//                            vtIndices.push_back(vertindexes[i * 3 + 1]);
//                            normalIndices.push_back(vertindexes[i * 3 + 2]);
//                        }
//                    }
//                    //����� �� ��������� ��������� �����, �������� ���� � ��� ��� �� �������
//                    cont = true;
//                }
//            }
//        }
//    }
//    // ������ ��������� �������� �������� � �������� �������� ��������
//    // ��� ������ ������� � ������� ��������, �������������� �������
//    // ��� ��������� �������� ��������� � �������� ������
//
//    size_t tmpsize = vertexIndices.size();
//    for (unsigned int i = 0; i < tmpsize; i++)
//    {
//        //���� ������ ��� ������� � ����� ���������� � 1!
//        glm::vec3 vertex = temp_vertices[vertexIndices[i] - 1];
//        outVertices.push_back(vertex);
//        glm::vec3 normal = temp_normals[normalIndices[i] - 1];
//        outNormals.push_back(normal);
//        glm::vec2 vt = temp_textures[vtIndices[i] - 1];
//        outTextures.push_back(vt);
//    }
//    return true;
//}


bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
) {
    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }

    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                fclose(file);
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else {
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

    }

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        glm::vec3 normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs.push_back(uv);
        out_normals.push_back(normal);

    }
    fclose(file);
    return true;
}

void genSphere(std::vector<GLuint>& outIndexes, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals, float radius, int sectorCount, int stackCount)
{
    //������� �������� ��������
    outIndexes.clear();
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();

    //��������������� ���������� ��� �������� ������������� ������
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;
    float sectorStep = 2.0f * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    //���� �� ������ ���������
    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // ������� �� PI/2 � �� -PI/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // �� ������ ��������� ����������� (sectorCount+1) ������
        // ��� ������ � ��������� ��������� ������� � �������, �� ���������� ���������� ����������
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // �� 0 �� 2PI

            // ������������� ���������� (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            glm::vec3 vert;
            vert.x = x;
            vert.y = y;
            vert.z = z;
            outVertices.push_back(vert);

            // ������������� ������ ������� (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            glm::vec3 norm;
            norm.x = nx;
            norm.y = ny;
            norm.z = nz;
            outNormals.push_back(norm);

            // ������������� ���������� ���������� (s, t) � ��������� [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            glm::vec2 vt;
            vt.s = s;
            vt.t = t;
            outTextures.push_back(vt);
        }

        //�� ��������� ���� - ����� ������� ������, �.�. �������
        int k1, k2;
        for (int i = 0; i < stackCount; ++i)
        {
            k1 = i * (sectorCount + 1);     // ������ �������� ���������
            k2 = k1 + sectorCount + 1;      // ������ ���������� ���������

            for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
            {
                // ��� ������ � ��������� ��������� �� 1 ������������, ��� ��������� - �� ���
                // k1 => k2 => k1+1
                if (i != 0)
                {
                    outIndexes.push_back(k1);
                    outIndexes.push_back(k2);
                    outIndexes.push_back(k1 + 1);
                }

                // k1+1 => k2 => k2+1
                if (i != (stackCount - 1))
                {
                    outIndexes.push_back(k1 + 1);
                    outIndexes.push_back(k2);
                    outIndexes.push_back(k2 + 1);
                }
            }
        }
    }
}

void genCylinder(std::vector<GLuint>& outIndexes, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals, float baseRadius, float topRadius, float height, int sectorCount, int stackCount)
{
    // ������� �������� ��������
    outIndexes.clear();
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();

    float radius;

    // ����� ��������������� �������
    std::vector<glm::vec3> unitVertices = getUnitCircleVertices(sectorCount);

    // ��������� ��������� ������ ������� ������
    // ����������� ��� ������ ������
    for (int i = 0; i < stackCount + 1; ++i)
    {
        //������ � ������ ������� ������
        float h = 0 + i * (height / stackCount);
        float t = 1.0f - i / stackCount;
        radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius);

        // ��� ������� ������� � ������ ������������� �������
        for (int j = 0, k = 0; j <= sectorCount; ++j, k++)
        {
            float ux = unitVertices[k].x;
            float uy = unitVertices[k].y;
            float uz = unitVertices[k].z;

            // ����������
            glm::vec3 v;
            v.x = ux * radius;
            v.y = uy * radius;
            v.z = h;
            outVertices.push_back(v);

            // ������ �������
            glm::vec3 n;
            n.x = ux;
            n.y = uy;
            n.z = uz;
            outNormals.push_back(n);

            //���������� ����������
            glm::vec2 vt;
            vt.s = (float)j / sectorCount;
            vt.t = t;
            outTextures.push_back(vt);

        }
    }

    // ������ ���� ������������� �������, ����������� ��������� � ��������
    // �� ������� ����������� ������� ������ � ����� ������� ���� ������
    int baseCenterIndex = (int)outVertices.size();
    int topCenterIndex = baseCenterIndex + sectorCount + 1;

    for (int i = 0; i < 2; ++i)
    {
        float h = 0 + i * height;
        float nz = (float)i;

        // ����������� �����
        outVertices.push_back(glm::vec3(0, 0, h));
        outNormals.push_back(glm::vec3(0, 0, nz));
        outTextures.push_back(glm::vec2(0.5, 0.5));

        radius = i ? topRadius : baseRadius;

        //��� ������ ������� � ������� ������������� ���������
        for (int j = 0, k = 0; j < sectorCount; ++j, k++)
        {
            float ux = unitVertices[k].x;
            float uy = unitVertices[k].y;
            // ����������
            outVertices.push_back(glm::vec3(ux * radius, uy * radius, h));

            // ������ �������
            outNormals.push_back(glm::vec3(0, 0, nz));

            // ���������� ����������
            outTextures.push_back(glm::vec2(-ux * 0.5f + 0.5f, -uy * 0.5f + 0.5f));

        }
    }

    //������ ������ ��������

    int k1 = 0;
    int k2 = sectorCount + 1;

    // ������� �����
    for (int i = 0; i < sectorCount * (stackCount + 2); ++i, ++k1, ++k2)
    {
        // �� ������ ������ �� ��� �����
        // k1 => k1+1 => k2
        outIndexes.push_back(k1);
        outIndexes.push_back(k1 + 1);
        outIndexes.push_back(k2);

        // k2 => k1+1 => k2+1
        outIndexes.push_back(k2);
        outIndexes.push_back(k1 + 1);
        outIndexes.push_back(k2 + 1);
    }

    // ������ ������� ��������� � ��������
    for (int i = 0, k = baseCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            outIndexes.push_back(baseCenterIndex);
            outIndexes.push_back(k + 1);
            outIndexes.push_back(k);
        }
        else
        {
            outIndexes.push_back(baseCenterIndex);
            outIndexes.push_back(baseCenterIndex + 1);
            outIndexes.push_back(k);
        }
    }

    for (int i = 0, k = topCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            outIndexes.push_back(topCenterIndex);
            outIndexes.push_back(k);
            outIndexes.push_back(k + 1);
        }
        else // �������� ��������� �����������
        {
            outIndexes.push_back(topCenterIndex);
            outIndexes.push_back(k);
            outIndexes.push_back(topCenterIndex + 1);
        }
    }
}

std::vector<glm::vec3> getUnitCircleVertices(int sectorCount)
{
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;

    std::vector<glm::vec3> unitCircleVertices;
    for (int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        glm::vec3 pos;
        pos.x = cos(sectorAngle);
        pos.y = sin(sectorAngle);
        pos.z = 0;
        unitCircleVertices.push_back(pos);
    }
    return unitCircleVertices;
}

void genTorus(std::vector<GLuint>& outIndexes, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals, float outerRadius, float tubeRadius, int sectorCount, int stackCount)
{
    //������� �������� ��������
    outIndexes.clear();
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();


    float du = 2 * PI / stackCount;
    float dv = 2 * PI / sectorCount;

    //��������� ������ ��� ������ ������
    for (size_t i = 0; i < stackCount; i++) {

        float u = i * du;

        //��������� ��� ������� ������� � ������
        for (size_t j = 0; j <= sectorCount; j++) {

            float v = (j % sectorCount) * dv;

            for (size_t k = 0; k < 2; k++)
            {
                float uu = u + k * du;

                // ����������
                float x = (outerRadius + tubeRadius * cos(v)) * cos(uu);
                float y = (outerRadius + tubeRadius * cos(v)) * sin(uu);
                float z = tubeRadius * sin(v);
                outVertices.push_back(glm::vec3(x, y, z));

                // ������ �������
                float nx = cos(v) * cos(uu);
                float ny = cos(v) * sin(uu);
                float nz = sin(v);
                outNormals.push_back(glm::vec3(nx, ny, nz));

                // ���������� ����������
                float tx = uu / (2 * PI);
                float ty = v / (2 * PI);
                outTextures.push_back(glm::vec2(tx, ty));

            }
            v += dv;
        }
    }

    // ������ �������� - ��� ���� �����. 
    // ���������� ����� ���� ������������ ��� ����� �������������
    // ������ �� ����� �� ���� ������������� � ����� �������������
    size_t size = outVertices.size();
    outIndexes.push_back(0);
    outIndexes.push_back(1);
    outIndexes.push_back(2);
    for (int k = 3; k < size; k++)
    {
        outIndexes.push_back(k - 2);
        outIndexes.push_back(k - 1);
        outIndexes.push_back(k);
    }
}
