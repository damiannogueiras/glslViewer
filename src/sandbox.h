#pragma once

#include "scene/scene.h"

#include "tools/fs.h"

enum ShaderType {
    FRAGMENT = 0,
    VERTEX = 1
};

class Sandbox {
public:
    Sandbox();
    
    // Main stages
    void                    setup(WatchFileList &_files, CommandList &_commands);
    bool                    reload();

    void                    flagChange() { m_change = true; }
    bool                    haveChange();
    void                    unfalgChange(); 

    void                    draw();
    void                    drawUI();
    void                    drawDone();

    void                    clear();
    
    bool                    isReady();

    void                    record( float _start, float _end );
    int                     getRecordedPorcentage();

    void                    addDefine( const std::string &_define );
    void                    delDefine( const std::string &_define );

    // Getting some data out of Sandbox
    std::string             getSource( ShaderType _type ) const;

    void                    printDependencies( ShaderType _type ) const;

    Scene&                  getScene() { return m_scene; }
    
    // Some events
    void                    onFileChange( WatchFileList &_files, int _index );
    void                    onScroll( float _yoffset );
    void                    onScreenshot( std::string _file );
    void                    onMouseDrag( float _x, float _y, int _button );
    void                    onViewportResize( int _newWidth, int _newHeight );
   
    // Include folders
    FileList                include_folders;

    // Defines
    List                    defines;

    // Uniforms
    Uniforms                uniforms;

    // Screenshot file
    std::string             screenshotFile;

    // States
    int                     frag_index;
    int                     vert_index;
    int                     geom_index;

    bool                    verbose;
    bool                    cursor;
    bool                    debug;

private:
    void                _updateBuffers();
    void                _updateDependencies(WatchFileList &_files);

    void                _renderBuffers();
    void                _renderBackground();

    // Main Shader
    std::string         m_frag_source;
    std::string         m_vert_source;

    // Dependencies
    FileList            m_vert_dependencies;
    FileList            m_frag_dependencies;
    Shader              m_shader;
    Vbo*                m_vbo;
 
    // Background
    Shader              m_background_shader;
    bool                m_background_enabled;

    // Buffers
    std::vector<Shader> m_buffers_shaders;
    int                 m_buffers_total;

    // Scene
    Scene               m_scene;
    Fbo                 m_scene_fbo;

    // Postprocessing
    Shader              m_postprocessing_shader;
    bool                m_postprocessing_enabled;

    // Billboard
    Shader              m_billboard_shader;
    Vbo*                m_billboard_vbo;
    
    // Cursor
    Shader              m_wireframe2D_shader;
    Vbo*                m_cross_vbo;

    // Recording
    Fbo                 m_record_fbo;
    float               m_record_start;
    float               m_record_head;
    float               m_record_end;
    int                 m_record_counter;
    bool                m_record;

    // Other state properties
    glm::mat3           m_view2d;
    unsigned int        m_frame;
    bool                m_change;
};
