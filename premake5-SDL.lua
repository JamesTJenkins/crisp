project "SDL"
	language "C++"
	cppdialect "C++14"

    location "Crisp/vendor/SDL2/VisualC/SDL"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"Crisp/vendor/SDL2/include"
	}

    flags {
		"MultiProcessorCompile"
	}
    
	vectorextensions "SSE"
	inlining "Explicit"
    intrinsics "off"

	-- Windows -- 
	filter "system:windows"
		kind "SharedLib"
		staticruntime "off"
        systemversion "latest"

		resoptions { "Crisp/vendor/SDL2/src/main/windows/version.rc", }

		flags {
			"NoRuntimeChecks",
			"NoBufferSecurityCheck"
		}
		
		defines {
			"DLL_EXPORT",
			"_WINDOWS"
		}

		links {
			"setupapi",
			"winmm",
			"imm32",
			"version"
		}

        postbuildcommands {
		    ("{COPY} %{cfg.buildtarget.relpath} \"%{cfg.buildtarget.relpath}/../../Game/\""),
		    ("{COPY} %{cfg.buildtarget.relpath} \"%{cfg.buildtarget.relpath}/../../CrispEditor/\"")
		}

		files {
			"Crisp/vendor/SDL2/include/begin_code.h", 
            "Crisp/vendor/SDL2/include/close_code.h", 
            "Crisp/vendor/SDL2/include/SDL.h", 
            "Crisp/vendor/SDL2/include/SDL_assert.h", 
            "Crisp/vendor/SDL2/include/SDL_atomic.h", 
            "Crisp/vendor/SDL2/include/SDL_audio.h", 
            "Crisp/vendor/SDL2/include/SDL_bits.h", 
            "Crisp/vendor/SDL2/include/SDL_blendmode.h", 
            "Crisp/vendor/SDL2/include/SDL_clipboard.h", 
            "Crisp/vendor/SDL2/include/SDL_config.h", 
            "Crisp/vendor/SDL2/include/SDL_config_windows.h", 
            "Crisp/vendor/SDL2/include/SDL_copying.h", 
            "Crisp/vendor/SDL2/include/SDL_cpuinfo.h", 
            "Crisp/vendor/SDL2/include/SDL_egl.h", 
            "Crisp/vendor/SDL2/include/SDL_endian.h", 
            "Crisp/vendor/SDL2/include/SDL_error.h", 
            "Crisp/vendor/SDL2/include/SDL_events.h", 
            "Crisp/vendor/SDL2/include/SDL_filesystem.h", 
            "Crisp/vendor/SDL2/include/SDL_gamecontroller.h", 
            "Crisp/vendor/SDL2/include/SDL_gesture.h", 
            "Crisp/vendor/SDL2/include/SDL_guid.h", 
            "Crisp/vendor/SDL2/include/SDL_haptic.h", 
            "Crisp/vendor/SDL2/include/SDL_hints.h", 
            "Crisp/vendor/SDL2/include/SDL_hidapi.h", 
            "Crisp/vendor/SDL2/include/SDL_joystick.h", 
            "Crisp/vendor/SDL2/include/SDL_keyboard.h", 
            "Crisp/vendor/SDL2/include/SDL_keycode.h", 
            "Crisp/vendor/SDL2/include/SDL_loadso.h", 
            "Crisp/vendor/SDL2/include/SDL_locale.h", 
            "Crisp/vendor/SDL2/include/SDL_log.h", 
            "Crisp/vendor/SDL2/include/SDL_main.h", 
            "Crisp/vendor/SDL2/include/SDL_messagebox.h", 
            "Crisp/vendor/SDL2/include/SDL_metal.h", 
            "Crisp/vendor/SDL2/include/SDL_misc.h", 
            "Crisp/vendor/SDL2/include/SDL_mouse.h", 
            "Crisp/vendor/SDL2/include/SDL_mutex.h", 
            "Crisp/vendor/SDL2/include/SDL_name.h", 
            "Crisp/vendor/SDL2/include/SDL_opengl.h", 
            "Crisp/vendor/SDL2/include/SDL_opengl_glext.h", 
            "Crisp/vendor/SDL2/include/SDL_opengles.h", 
            "Crisp/vendor/SDL2/include/SDL_opengles2.h", 
            "Crisp/vendor/SDL2/include/SDL_opengles2_gl2.h", 
            "Crisp/vendor/SDL2/include/SDL_opengles2_gl2ext.h", 
            "Crisp/vendor/SDL2/include/SDL_opengles2_gl2platform.h", 
            "Crisp/vendor/SDL2/include/SDL_opengles2_khrplatform.h", 
            "Crisp/vendor/SDL2/include/SDL_pixels.h", 
            "Crisp/vendor/SDL2/include/SDL_platform.h", 
            "Crisp/vendor/SDL2/include/SDL_power.h", 
            "Crisp/vendor/SDL2/include/SDL_quit.h", 
            "Crisp/vendor/SDL2/include/SDL_rect.h", 
            "Crisp/vendor/SDL2/include/SDL_render.h", 
            "Crisp/vendor/SDL2/include/SDL_revision.h", 
            "Crisp/vendor/SDL2/include/SDL_rwops.h", 
            "Crisp/vendor/SDL2/include/SDL_scancode.h", 
            "Crisp/vendor/SDL2/include/SDL_sensor.h", 
            "Crisp/vendor/SDL2/include/SDL_shape.h", 
            "Crisp/vendor/SDL2/include/SDL_stdinc.h", 
            "Crisp/vendor/SDL2/include/SDL_surface.h", 
            "Crisp/vendor/SDL2/include/SDL_system.h", 
            "Crisp/vendor/SDL2/include/SDL_syswm.h", 
            "Crisp/vendor/SDL2/include/SDL_test.h", 
            "Crisp/vendor/SDL2/include/SDL_test_assert.h", 
            "Crisp/vendor/SDL2/include/SDL_test_common.h", 
            "Crisp/vendor/SDL2/include/SDL_test_compare.h", 
            "Crisp/vendor/SDL2/include/SDL_test_crc32.h", 
            "Crisp/vendor/SDL2/include/SDL_test_font.h", 
            "Crisp/vendor/SDL2/include/SDL_test_fuzzer.h", 
            "Crisp/vendor/SDL2/include/SDL_test_harness.h", 
            "Crisp/vendor/SDL2/include/SDL_test_images.h", 
            "Crisp/vendor/SDL2/include/SDL_test_log.h", 
            "Crisp/vendor/SDL2/include/SDL_test_md5.h", 
            "Crisp/vendor/SDL2/include/SDL_test_memory.h", 
            "Crisp/vendor/SDL2/include/SDL_test_random.h", 
            "Crisp/vendor/SDL2/include/SDL_thread.h", 
            "Crisp/vendor/SDL2/include/SDL_timer.h", 
            "Crisp/vendor/SDL2/include/SDL_touch.h", 
            "Crisp/vendor/SDL2/include/SDL_types.h", 
            "Crisp/vendor/SDL2/include/SDL_version.h", 
            "Crisp/vendor/SDL2/include/SDL_video.h", 
            "Crisp/vendor/SDL2/include/SDL_vulkan.h", 
            "Crisp/vendor/SDL2/src/audio/directsound/SDL_directsound.h", 
            "Crisp/vendor/SDL2/src/audio/disk/SDL_diskaudio.h", 
            "Crisp/vendor/SDL2/src/audio/dummy/SDL_dummyaudio.h", 
            "Crisp/vendor/SDL2/src/audio/SDL_audio_c.h", 
            "Crisp/vendor/SDL2/src/audio/SDL_audiodev_c.h", 
            "Crisp/vendor/SDL2/src/audio/SDL_sysaudio.h", 
            "Crisp/vendor/SDL2/src/audio/SDL_wave.h", 
            "Crisp/vendor/SDL2/src/audio/wasapi/SDL_wasapi.h", 
            "Crisp/vendor/SDL2/src/audio/winmm/SDL_winmm.h", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_directx.h", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_hid.h", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_immdevice.h", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_windows.h", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_xinput.h", 
            "Crisp/vendor/SDL2/src/dynapi/SDL_dynapi.h", 
            "Crisp/vendor/SDL2/src/dynapi/SDL_dynapi_overrides.h", 
            "Crisp/vendor/SDL2/src/dynapi/SDL_dynapi_procs.h", 
            "Crisp/vendor/SDL2/src/events/blank_cursor.h", 
            "Crisp/vendor/SDL2/src/events/default_cursor.h", 
            "Crisp/vendor/SDL2/src/events/scancodes_windows.h", 
            "Crisp/vendor/SDL2/src/events/SDL_clipboardevents_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_displayevents_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_dropevents_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_events_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_gesture_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_keyboard_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_mouse_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_touch_c.h", 
            "Crisp/vendor/SDL2/src/events/SDL_windowevents_c.h", 
            "Crisp/vendor/SDL2/src/haptic/SDL_haptic_c.h", 
            "Crisp/vendor/SDL2/src/haptic/SDL_syshaptic.h", 
            "Crisp/vendor/SDL2/src/haptic/windows/SDL_dinputhaptic_c.h", 
            "Crisp/vendor/SDL2/src/haptic/windows/SDL_windowshaptic_c.h", 
            "Crisp/vendor/SDL2/src/haptic/windows/SDL_xinputhaptic_c.h", 
            "Crisp/vendor/SDL2/src/hidapi/hidapi/hidapi.h", 
            "Crisp/vendor/SDL2/src/hidapi/SDL_hidapi_c.h", 
            "Crisp/vendor/SDL2/src/joystick/controller_type.h", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapijoystick_c.h", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_rumble.h", 
            "Crisp/vendor/SDL2/src/joystick/SDL_gamecontrollerdb.h", 
            "Crisp/vendor/SDL2/src/joystick/SDL_joystick_c.h", 
            "Crisp/vendor/SDL2/src/joystick/SDL_sysjoystick.h", 
            "Crisp/vendor/SDL2/src/joystick/usb_ids.h", 
            "Crisp/vendor/SDL2/src/joystick/virtual/SDL_virtualjoystick_c.h", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_dinputjoystick_c.h", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_rawinputjoystick_c.h", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_windowsjoystick_c.h", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_xinputjoystick_c.h", 
            "Crisp/vendor/SDL2/src/libm/math_libm.h", 
            "Crisp/vendor/SDL2/src/libm/math_private.h", 
            "Crisp/vendor/SDL2/src/locale/SDL_syslocale.h", 
            "Crisp/vendor/SDL2/src/misc/SDL_sysurl.h", 
            "Crisp/vendor/SDL2/src/power/SDL_syspower.h", 
            "Crisp/vendor/SDL2/src/render/direct3d11/SDL_shaders_d3d11.h", 
            "Crisp/vendor/SDL2/src/render/direct3d12/SDL_shaders_d3d12.h", 
            "Crisp/vendor/SDL2/src/render/direct3d/SDL_shaders_d3d.h", 
            "Crisp/vendor/SDL2/src/render/opengles2/SDL_gles2funcs.h", 
            "Crisp/vendor/SDL2/src/render/opengles2/SDL_shaders_gles2.h", 
            "Crisp/vendor/SDL2/src/render/opengl/SDL_glfuncs.h", 
            "Crisp/vendor/SDL2/src/render/opengl/SDL_shaders_gl.h", 
            "Crisp/vendor/SDL2/src/render/SDL_d3dmath.h", 
            "Crisp/vendor/SDL2/src/render/SDL_sysrender.h", 
            "Crisp/vendor/SDL2/src/render/SDL_yuv_sw_c.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_blendfillrect.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_blendline.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_blendpoint.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_draw.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_drawline.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_drawpoint.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_render_sw_c.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_rotate.h", 
            "Crisp/vendor/SDL2/src/render/software/SDL_triangle.h", 
            "Crisp/vendor/SDL2/src/SDL_assert_c.h", 
            "Crisp/vendor/SDL2/src/SDL_dataqueue.h", 
            "Crisp/vendor/SDL2/src/SDL_error_c.h", 
            "Crisp/vendor/SDL2/src/SDL_guid.c", 
            "Crisp/vendor/SDL2/src/SDL_hints_c.h", 
            "Crisp/vendor/SDL2/src/SDL_internal.h", 
            "Crisp/vendor/SDL2/src/SDL_list.h", 
            "Crisp/vendor/SDL2/src/SDL_log_c.h", 
            "Crisp/vendor/SDL2/src/sensor/dummy/SDL_dummysensor.h", 
            "Crisp/vendor/SDL2/src/sensor/SDL_sensor_c.h", 
            "Crisp/vendor/SDL2/src/sensor/SDL_syssensor.h", 
            "Crisp/vendor/SDL2/src/sensor/windows/SDL_windowssensor.h", 
            "Crisp/vendor/SDL2/src/thread/SDL_systhread.h", 
            "Crisp/vendor/SDL2/src/thread/SDL_thread_c.h", 
            "Crisp/vendor/SDL2/src/thread/generic/SDL_syscond_c.h", 
            "Crisp/vendor/SDL2/src/thread/windows/SDL_sysmutex_c.h", 
            "Crisp/vendor/SDL2/src/thread/windows/SDL_systhread_c.h", 
            "Crisp/vendor/SDL2/src/timer/SDL_timer_c.h", 
            "Crisp/vendor/SDL2/src/video/dummy/SDL_nullevents_c.h", 
            "Crisp/vendor/SDL2/src/video/dummy/SDL_nullframebuffer_c.h", 
            "Crisp/vendor/SDL2/src/video/dummy/SDL_nullvideo.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vk_icd.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vk_layer.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vk_platform.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vk_sdk_platform.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan.hpp", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_android.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_beta.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_core.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_directfb.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_fuchsia.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_ggp.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_ios.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_macos.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_metal.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_vi.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_wayland.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_win32.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_xcb.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_xlib.h", 
            "Crisp/vendor/SDL2/src/video/khronos/vulkan/vulkan_xlib_xrandr.h", 
            "Crisp/vendor/SDL2/src/video/SDL_blit.h", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_auto.h", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_copy.h", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_slow.h", 
            "Crisp/vendor/SDL2/src/video/SDL_egl_c.h", 
            "Crisp/vendor/SDL2/src/video/SDL_pixels_c.h", 
            "Crisp/vendor/SDL2/src/video/SDL_rect_c.h", 
            "Crisp/vendor/SDL2/src/video/SDL_RLEaccel_c.h", 
            "Crisp/vendor/SDL2/src/video/SDL_shape_internals.h", 
            "Crisp/vendor/SDL2/src/video/SDL_sysvideo.h", 
            "Crisp/vendor/SDL2/src/video/SDL_vulkan_internal.h", 
            "Crisp/vendor/SDL2/src/video/SDL_yuv_c.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_msctf.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_vkeys.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsclipboard.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsevents.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsframebuffer.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowskeyboard.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsmessagebox.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsmodes.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsmouse.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsopengl.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsopengles.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsshape.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsvideo.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsvulkan.h", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowswindow.h", 
            "Crisp/vendor/SDL2/src/video/windows/wmmsg.h", 
            "Crisp/vendor/SDL2/src/video/yuv2rgb/yuv_rgb.h", 
            "Crisp/vendor/SDL2/src/video/yuv2rgb/yuv_rgb_sse_func.h", 
            "Crisp/vendor/SDL2/src/video/yuv2rgb/yuv_rgb_std_func.h", 
            "Crisp/vendor/SDL2/src/atomic/SDL_atomic.c", 
            "Crisp/vendor/SDL2/src/atomic/SDL_spinlock.c", 
            "Crisp/vendor/SDL2/src/audio/directsound/SDL_directsound.c", 
            "Crisp/vendor/SDL2/src/audio/disk/SDL_diskaudio.c", 
            "Crisp/vendor/SDL2/src/audio/dummy/SDL_dummyaudio.c", 
            "Crisp/vendor/SDL2/src/audio/SDL_audio.c", 
            "Crisp/vendor/SDL2/src/audio/SDL_audiocvt.c", 
            "Crisp/vendor/SDL2/src/audio/SDL_audiodev.c", 
            "Crisp/vendor/SDL2/src/audio/SDL_audiotypecvt.c", 
            "Crisp/vendor/SDL2/src/audio/SDL_mixer.c", 
            "Crisp/vendor/SDL2/src/audio/SDL_wave.c", 
            "Crisp/vendor/SDL2/src/audio/winmm/SDL_winmm.c", 
            "Crisp/vendor/SDL2/src/audio/wasapi/SDL_wasapi.c", 
            "Crisp/vendor/SDL2/src/audio/wasapi/SDL_wasapi_win32.c", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_hid.c", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_immdevice.c", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_windows.c", 
            "Crisp/vendor/SDL2/src/core/windows/SDL_xinput.c", 
            "Crisp/vendor/SDL2/src/cpuinfo/SDL_cpuinfo.c", 
            "Crisp/vendor/SDL2/src/dynapi/SDL_dynapi.c", 
            "Crisp/vendor/SDL2/src/events/SDL_clipboardevents.c", 
            "Crisp/vendor/SDL2/src/events/SDL_displayevents.c", 
            "Crisp/vendor/SDL2/src/events/SDL_dropevents.c", 
            "Crisp/vendor/SDL2/src/events/SDL_events.c", 
            "Crisp/vendor/SDL2/src/events/SDL_gesture.c", 
            "Crisp/vendor/SDL2/src/events/SDL_keyboard.c", 
            "Crisp/vendor/SDL2/src/events/SDL_mouse.c", 
            "Crisp/vendor/SDL2/src/events/SDL_quit.c", 
            "Crisp/vendor/SDL2/src/events/SDL_touch.c", 
            "Crisp/vendor/SDL2/src/events/SDL_windowevents.c", 
            "Crisp/vendor/SDL2/src/file/SDL_rwops.c", 
            "Crisp/vendor/SDL2/src/filesystem/windows/SDL_sysfilesystem.c", 
            "Crisp/vendor/SDL2/src/haptic/dummy/SDL_syshaptic.c", 
            "Crisp/vendor/SDL2/src/haptic/SDL_haptic.c", 
            "Crisp/vendor/SDL2/src/haptic/windows/SDL_dinputhaptic.c", 
            "Crisp/vendor/SDL2/src/haptic/windows/SDL_windowshaptic.c", 
            "Crisp/vendor/SDL2/src/haptic/windows/SDL_xinputhaptic.c", 
            "Crisp/vendor/SDL2/src/hidapi/SDL_hidapi.c", 
            "Crisp/vendor/SDL2/src/joystick/controller_type.c", 
            "Crisp/vendor/SDL2/src/joystick/dummy/SDL_sysjoystick.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapijoystick.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_combined.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_gamecube.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_luna.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_ps3.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_ps4.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_ps5.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_rumble.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_shield.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_stadia.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_steam.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_switch.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_wii.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_xbox360.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_xbox360w.c", 
            "Crisp/vendor/SDL2/src/joystick/hidapi/SDL_hidapi_xboxone.c", 
            "Crisp/vendor/SDL2/src/joystick/SDL_gamecontroller.c", 
            "Crisp/vendor/SDL2/src/joystick/SDL_joystick.c", 
            "Crisp/vendor/SDL2/src/joystick/virtual/SDL_virtualjoystick.c", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_dinputjoystick.c", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_rawinputjoystick.c", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_windowsjoystick.c", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_windows_gaming_input.c", 
            "Crisp/vendor/SDL2/src/joystick/windows/SDL_xinputjoystick.c", 
            "Crisp/vendor/SDL2/src/libm/e_atan2.c", 
            "Crisp/vendor/SDL2/src/libm/e_exp.c", 
            "Crisp/vendor/SDL2/src/libm/e_fmod.c", 
            "Crisp/vendor/SDL2/src/libm/e_log.c", 
            "Crisp/vendor/SDL2/src/libm/e_log10.c", 
            "Crisp/vendor/SDL2/src/libm/e_pow.c", 
            "Crisp/vendor/SDL2/src/libm/e_rem_pio2.c", 
            "Crisp/vendor/SDL2/src/libm/e_sqrt.c", 
            "Crisp/vendor/SDL2/src/libm/k_cos.c", 
            "Crisp/vendor/SDL2/src/libm/k_rem_pio2.c", 
            "Crisp/vendor/SDL2/src/libm/k_sin.c", 
            "Crisp/vendor/SDL2/src/libm/k_tan.c", 
            "Crisp/vendor/SDL2/src/libm/s_atan.c", 
            "Crisp/vendor/SDL2/src/libm/s_copysign.c", 
            "Crisp/vendor/SDL2/src/libm/s_cos.c", 
            "Crisp/vendor/SDL2/src/libm/s_fabs.c", 
            "Crisp/vendor/SDL2/src/libm/s_floor.c", 
            "Crisp/vendor/SDL2/src/libm/s_scalbn.c", 
            "Crisp/vendor/SDL2/src/libm/s_sin.c", 
            "Crisp/vendor/SDL2/src/libm/s_tan.c", 
            "Crisp/vendor/SDL2/src/loadso/windows/SDL_sysloadso.c", 
            "Crisp/vendor/SDL2/src/locale/SDL_locale.c", 
            "Crisp/vendor/SDL2/src/locale/windows/SDL_syslocale.c", 
            "Crisp/vendor/SDL2/src/misc/SDL_url.c", 
            "Crisp/vendor/SDL2/src/misc/windows/SDL_sysurl.c", 
            "Crisp/vendor/SDL2/src/power/SDL_power.c", 
            "Crisp/vendor/SDL2/src/power/windows/SDL_syspower.c", 
            "Crisp/vendor/SDL2/src/render/direct3d11/SDL_shaders_d3d11.c", 
            "Crisp/vendor/SDL2/src/render/direct3d12/SDL_render_d3d12.c", 
            "Crisp/vendor/SDL2/src/render/direct3d12/SDL_shaders_d3d12.c", 
            "Crisp/vendor/SDL2/src/render/direct3d/SDL_render_d3d.c", 
            "Crisp/vendor/SDL2/src/render/direct3d11/SDL_render_d3d11.c", 
            "Crisp/vendor/SDL2/src/render/direct3d/SDL_shaders_d3d.c", 
            "Crisp/vendor/SDL2/src/render/opengl/SDL_render_gl.c", 
            "Crisp/vendor/SDL2/src/render/opengl/SDL_shaders_gl.c", 
            "Crisp/vendor/SDL2/src/render/opengles2/SDL_render_gles2.c", 
            "Crisp/vendor/SDL2/src/render/opengles2/SDL_shaders_gles2.c", 
            "Crisp/vendor/SDL2/src/render/SDL_d3dmath.c", 
            "Crisp/vendor/SDL2/src/render/SDL_render.c", 
            "Crisp/vendor/SDL2/src/render/SDL_yuv_sw.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_blendfillrect.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_blendline.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_blendpoint.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_drawline.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_drawpoint.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_render_sw.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_rotate.c", 
            "Crisp/vendor/SDL2/src/render/software/SDL_triangle.c", 
            "Crisp/vendor/SDL2/src/SDL.c", 
            "Crisp/vendor/SDL2/src/SDL_assert.c", 
            "Crisp/vendor/SDL2/src/SDL_dataqueue.c", 
            "Crisp/vendor/SDL2/src/SDL_list.c", 
            "Crisp/vendor/SDL2/src/SDL_error.c", 
            "Crisp/vendor/SDL2/src/SDL_hints.c", 
            "Crisp/vendor/SDL2/src/SDL_log.c", 
            "Crisp/vendor/SDL2/src/SDL_utils.c", 
            "Crisp/vendor/SDL2/src/sensor/dummy/SDL_dummysensor.c", 
            "Crisp/vendor/SDL2/src/sensor/SDL_sensor.c", 
            "Crisp/vendor/SDL2/src/sensor/windows/SDL_windowssensor.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_crc16.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_crc32.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_getenv.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_iconv.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_malloc.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_mslibc.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_qsort.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_stdlib.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_string.c", 
            "Crisp/vendor/SDL2/src/stdlib/SDL_strtokr.c", 
            "Crisp/vendor/SDL2/src/thread/generic/SDL_syscond.c", 
            "Crisp/vendor/SDL2/src/thread/SDL_thread.c", 
            "Crisp/vendor/SDL2/src/thread/windows/SDL_syscond_cv.c", 
            "Crisp/vendor/SDL2/src/thread/windows/SDL_sysmutex.c", 
            "Crisp/vendor/SDL2/src/thread/windows/SDL_syssem.c", 
            "Crisp/vendor/SDL2/src/thread/windows/SDL_systhread.c", 
            "Crisp/vendor/SDL2/src/thread/windows/SDL_systls.c", 
            "Crisp/vendor/SDL2/src/timer/SDL_timer.c", 
            "Crisp/vendor/SDL2/src/timer/windows/SDL_systimer.c", 
            "Crisp/vendor/SDL2/src/video/dummy/SDL_nullevents.c", 
            "Crisp/vendor/SDL2/src/video/dummy/SDL_nullframebuffer.c", 
            "Crisp/vendor/SDL2/src/video/dummy/SDL_nullvideo.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_0.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_1.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_A.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_auto.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_copy.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_N.c", 
            "Crisp/vendor/SDL2/src/video/SDL_blit_slow.c", 
            "Crisp/vendor/SDL2/src/video/SDL_bmp.c", 
            "Crisp/vendor/SDL2/src/video/SDL_clipboard.c", 
            "Crisp/vendor/SDL2/src/video/SDL_egl.c", 
            "Crisp/vendor/SDL2/src/video/SDL_fillrect.c", 
            "Crisp/vendor/SDL2/src/video/SDL_pixels.c", 
            "Crisp/vendor/SDL2/src/video/SDL_rect.c", 
            "Crisp/vendor/SDL2/src/video/SDL_RLEaccel.c", 
            "Crisp/vendor/SDL2/src/video/SDL_shape.c", 
            "Crisp/vendor/SDL2/src/video/SDL_stretch.c", 
            "Crisp/vendor/SDL2/src/video/SDL_surface.c", 
            "Crisp/vendor/SDL2/src/video/SDL_video.c", 
            "Crisp/vendor/SDL2/src/video/SDL_vulkan_utils.c", 
            "Crisp/vendor/SDL2/src/video/SDL_yuv.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsclipboard.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsevents.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsframebuffer.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowskeyboard.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsmessagebox.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsmodes.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsmouse.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsopengl.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsopengles.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsshape.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsvideo.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowsvulkan.c", 
            "Crisp/vendor/SDL2/src/video/windows/SDL_windowswindow.c", 
            "Crisp/vendor/SDL2/src/video/yuv2rgb/yuv_rgb.c", 
		}

	-- Mac --
	filter "system:macosx"
		kind "StaticLib"
		staticruntime "on"

	-- Linux --
	filter "system:linux"
		kind "StaticLib"
		staticruntime "on"

	filter "configurations:Debug"
		defines "_DEBUG"
        runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG"
        runtime "Release"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "NDEBUG"
        runtime "Release"
		optimize "On"