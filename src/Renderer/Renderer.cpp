#include "Renderer.hpp"

#include "../Scene/Scene.hpp"
#include "../Scene/Entity.hpp"
#include "../Scene/Components.hpp"


Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);
}

Renderer::~Renderer()
{

}

void Renderer::Render(Scene* scene)
{
    glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render scene
    DrawMeshes(scene);
}

void Renderer::DrawMeshes(Scene* scene)
{
    auto render_view = scene->GetRegistry().view<TransformComponent, MeshComponent, MaterialComponent>();
    auto camera_view = scene->GetRegistry().view<CameraComponent>();

    Camera cam;
    Entity ent = {entt::null, nullptr};
    for(auto e : camera_view)
    {
        ent = {e, scene};
        CameraComponent& component = ent.GetComponent<CameraComponent>();
        if(component.primary)
        {
            cam = component.camera;
            break;
        }
    }

    auto trans = ent.GetComponent<TransformComponent>();
    auto pos = trans.translation;
    glm::mat4 view_matrix = glm::lookAt(pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = cam.GetProjection();
    glm::mat4 normal = glm::transpose(glm::inverse(glm::mat4(1.0f)));
    glm::vec3 light = glm::vec3(-10.0f, 20.0f, 10.0f);

    for(auto e : render_view)
    {
        Entity entity(e, scene);
        auto transform = entity.GetComponent<TransformComponent>();
        auto mesh = entity.GetComponent<MeshComponent>();
        auto material = entity.GetComponent<MaterialComponent>();
        model = glm::translate(model, transform.translation);
        glm::mat4 normal = glm::transpose(glm::inverse(model));
        material.shader->Use();
        // Set Uniforms
        material.shader->SetUniformMat4fv("model", model);
        material.shader->SetUniformMat4fv("view", view_matrix);
        material.shader->SetUniformMat4fv("projection", projection);
        material.shader->SetUniformMat4fv("normal_matrix", normal);
        material.shader->SetUniform3f("LightPos", light);
        material.shader->SetUniform3f("ViewPos", pos);

        glBindVertexArray(mesh.mesh->GetVAO());
        glDrawElements(GL_TRIANGLES, mesh.mesh->p_indices.size(), GL_UNSIGNED_INT, 0);
    }
}