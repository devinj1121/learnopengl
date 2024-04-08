#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures):
vertices(vertices), indices(indices), textures(textures){

    // Sets up the VAO and attribute pointers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertex attribute pointers
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bittangent));

    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);

}

void Mesh::Draw(Shader &shader) 
{

    // First link the textures to appropriate uniforms in shader and bind them
    unsigned int i_diffuse  = 1;
    unsigned int i_specular = 1;
    unsigned int i_normal  = 1;
    unsigned int i_height  = 1;

    // Loop through the textures of the mesh
    for(unsigned int i = 0; i < textures.size(); i++){

        glActiveTexture(GL_TEXTURE0 + i); // activate a new slot for it
        std::string ith;

        if(textures[i].type == "texture_diffuse")
            ith = std::to_string(i_diffuse++);

        else if(textures[i].type == "texture_specular")
            ith = std::to_string(i_specular++);

        else if(textures[i].type == "texture_normal")
            ith = std::to_string(i_normal++);
            
        else if(textures[i].type == "texture_height")
            ith = std::to_string(i_height++);

        // Link with the corresponding shader uniform and bind
        glUniform1i(glGetUniformLocation(shader.ID, (textures[i].type + ith).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    
    // Next, draw call
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

    // Cleanup
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
