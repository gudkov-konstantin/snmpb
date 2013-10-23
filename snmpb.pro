QT       += core gui svg concurrent printsupport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE	= app
TARGET          = snmpb

PRECOMPILED_HEADER = stdafx.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
 DEFINES += USING_PCH
}

gcc*:QMAKE_CXXFLAGS+="-std=c++11"
clang*:QMAKE_CXXFLAGS+="-std=c++11"

SOURCES	+= \
    snmp_pp/address.cpp \
    snmp_pp/asn1.cpp \
    snmp_pp/auth_priv.cpp \
    snmp_pp/counter.cpp \
    snmp_pp/ctr64.cpp \
    snmp_pp/eventlist.cpp \
    snmp_pp/eventlistholder.cpp \
    snmp_pp/gauge.cpp \
    snmp_pp/idea.cpp \
    snmp_pp/integer.cpp \
    snmp_pp/log.cpp \
    snmp_pp/md5c.cpp \
    snmp_pp/mp_v3.cpp \
    snmp_pp/msec.cpp \
    snmp_pp/msgqueue.cpp \
    snmp_pp/notifyqueue.cpp \
    snmp_pp/octet.cpp \
    snmp_pp/oid.cpp \
    snmp_pp/pdu.cpp \
    snmp_pp/reentrant.cpp \
    snmp_pp/sha.cpp \
    snmp_pp/snmpmsg.cpp \
    snmp_pp/target.cpp \
    snmp_pp/timetick.cpp \
    snmp_pp/usm_v3.cpp \
    snmp_pp/uxsnmp.cpp \
    snmp_pp/v3.cpp \
    snmp_pp/vb.cpp \
    snmp_pp/IPv6Utility.cpp \
    main.cpp \
    snmpb.cpp \
    mibnode.cpp \
    mibview.cpp \
    mibmodule.cpp \
    agent.cpp \
    trap.cpp \
    graph.cpp \
    comboboxes.cpp \
    mibhighlighter.cpp \
    markerwidget.cpp \
    mibeditor.cpp \
    mibtextedit.cpp \
    mibselection.cpp \
    logsnmpb.cpp \
    discovery.cpp \
    agentprofile.cpp \
    usmprofile.cpp \
    preferences.cpp \
    stdafx.cpp \
    qwt/qwt_widget_overlay.cpp \
    qwt/qwt_wheel.cpp \
    qwt/qwt_transform.cpp \
    qwt/qwt_thermo.cpp \
    qwt/qwt_text.cpp \
    qwt/qwt_text_label.cpp \
    qwt/qwt_text_engine.cpp \
    qwt/qwt_system_clock.cpp \
    qwt/qwt_symbol.cpp \
    qwt/qwt_spline.cpp \
    qwt/qwt_slider.cpp \
    qwt/qwt_series_data.cpp \
    qwt/qwt_scale_widget.cpp \
    qwt/qwt_scale_map.cpp \
    qwt/qwt_scale_engine.cpp \
    qwt/qwt_scale_draw.cpp \
    qwt/qwt_scale_div.cpp \
    qwt/qwt_sampling_thread.cpp \
    qwt/qwt_round_scale_draw.cpp \
    qwt/qwt_raster_data.cpp \
    qwt/qwt_point_polar.cpp \
    qwt/qwt_point_mapper.cpp \
    qwt/qwt_point_data.cpp \
    qwt/qwt_point_3d.cpp \
    qwt/qwt_plot.cpp \
    qwt/qwt_plot_zoomer.cpp \
    qwt/qwt_plot_zoneitem.cpp \
    qwt/qwt_plot_xml.cpp \
    qwt/qwt_plot_tradingcurve.cpp \
    qwt/qwt_plot_textlabel.cpp \
    qwt/qwt_plot_svgitem.cpp \
    qwt/qwt_plot_spectrogram.cpp \
    qwt/qwt_plot_spectrocurve.cpp \
    qwt/qwt_plot_shapeitem.cpp \
    qwt/qwt_plot_seriesitem.cpp \
    qwt/qwt_plot_scaleitem.cpp \
    qwt/qwt_plot_rescaler.cpp \
    qwt/qwt_plot_renderer.cpp \
    qwt/qwt_plot_rasteritem.cpp \
    qwt/qwt_plot_picker.cpp \
    qwt/qwt_plot_panner.cpp \
    qwt/qwt_plot_multi_barchart.cpp \
    qwt/qwt_plot_marker.cpp \
    qwt/qwt_plot_magnifier.cpp \
    qwt/qwt_plot_legenditem.cpp \
    qwt/qwt_plot_layout.cpp \
    qwt/qwt_plot_item.cpp \
    qwt/qwt_plot_intervalcurve.cpp \
    qwt/qwt_plot_histogram.cpp \
    qwt/qwt_plot_grid.cpp \
    qwt/qwt_plot_glcanvas.cpp \
    qwt/qwt_plot_directpainter.cpp \
    qwt/qwt_plot_dict.cpp \
    qwt/qwt_plot_curve.cpp \
    qwt/qwt_plot_canvas.cpp \
    qwt/qwt_plot_barchart.cpp \
    qwt/qwt_plot_axis.cpp \
    qwt/qwt_plot_abstract_barchart.cpp \
    qwt/qwt_pixel_matrix.cpp \
    qwt/qwt_picker.cpp \
    qwt/qwt_picker_machine.cpp \
    qwt/qwt_panner.cpp \
    qwt/qwt_painter.cpp \
    qwt/qwt_painter_command.cpp \
    qwt/qwt_null_paintdevice.cpp \
    qwt/qwt_matrix_raster_data.cpp \
    qwt/qwt_math.cpp \
    qwt/qwt_magnifier.cpp \
    qwt/qwt_legend.cpp \
    qwt/qwt_legend_label.cpp \
    qwt/qwt_legend_data.cpp \
    qwt/qwt_knob.cpp \
    qwt/qwt_interval.cpp \
    qwt/qwt_interval_symbol.cpp \
    qwt/qwt_graphic.cpp \
    qwt/qwt_event_pattern.cpp \
    qwt/qwt_dyngrid_layout.cpp \
    qwt/qwt_dial.cpp \
    qwt/qwt_dial_needle.cpp \
    qwt/qwt_date.cpp \
    qwt/qwt_date_scale_engine.cpp \
    qwt/qwt_date_scale_draw.cpp \
    qwt/qwt_curve_fitter.cpp \
    qwt/qwt_counter.cpp \
    qwt/qwt_compass.cpp \
    qwt/qwt_compass_rose.cpp \
    qwt/qwt_column_symbol.cpp \
    qwt/qwt_color_map.cpp \
    qwt/qwt_clipper.cpp \
    qwt/qwt_arrow_button.cpp \
    qwt/qwt_analog_clock.cpp \
    qwt/qwt_abstract_slider.cpp \
    qwt/qwt_abstract_scale.cpp \
    qwt/qwt_abstract_scale_draw.cpp \
    qwt/qwt_abstract_legend.cpp \
    snmp_pp/collect.cpp

HEADERS	+= \
    snmpb.h \
    snmpbapp.h \
    mibnode.h \
    mibview.h \
    mibmodule.h \
    agent.h \
    trap.h \
    graph.h \
    comboboxes.h \
    mibhighlighter.h \
    markerwidget.h \
    mibeditor.h \
    mibtextedit.h \
    mibselection.h \
    logsnmpb.h \
    discovery.h \
    agentprofile.h \
    usmprofile.h \
    preferences.h \
    stdafx.h \
    qwt/qwt.h \
    qwt/qwt_widget_overlay.h \
    qwt/qwt_wheel.h \
    qwt/qwt_transform.h \
    qwt/qwt_thermo.h \
    qwt/qwt_text.h \
    qwt/qwt_text_label.h \
    qwt/qwt_text_engine.h \
    qwt/qwt_system_clock.h \
    qwt/qwt_symbol.h \
    qwt/qwt_spline.h \
    qwt/qwt_slider.h \
    qwt/qwt_series_store.h \
    qwt/qwt_series_data.h \
    qwt/qwt_scale_widget.h \
    qwt/qwt_scale_map.h \
    qwt/qwt_scale_engine.h \
    qwt/qwt_scale_draw.h \
    qwt/qwt_scale_div.h \
    qwt/qwt_sampling_thread.h \
    qwt/qwt_samples.h \
    qwt/qwt_round_scale_draw.h \
    qwt/qwt_raster_data.h \
    qwt/qwt_point_polar.h \
    qwt/qwt_point_mapper.h \
    qwt/qwt_point_data.h \
    qwt/qwt_point_3d.h \
    qwt/qwt_plot.h \
    qwt/qwt_plot_zoomer.h \
    qwt/qwt_plot_zoneitem.h \
    qwt/qwt_plot_tradingcurve.h \
    qwt/qwt_plot_textlabel.h \
    qwt/qwt_plot_svgitem.h \
    qwt/qwt_plot_spectrogram.h \
    qwt/qwt_plot_spectrocurve.h \
    qwt/qwt_plot_shapeitem.h \
    qwt/qwt_plot_seriesitem.h \
    qwt/qwt_plot_scaleitem.h \
    qwt/qwt_plot_rescaler.h \
    qwt/qwt_plot_renderer.h \
    qwt/qwt_plot_rasteritem.h \
    qwt/qwt_plot_picker.h \
    qwt/qwt_plot_panner.h \
    qwt/qwt_plot_multi_barchart.h \
    qwt/qwt_plot_marker.h \
    qwt/qwt_plot_magnifier.h \
    qwt/qwt_plot_legenditem.h \
    qwt/qwt_plot_layout.h \
    qwt/qwt_plot_item.h \
    qwt/qwt_plot_intervalcurve.h \
    qwt/qwt_plot_histogram.h \
    qwt/qwt_plot_grid.h \
    qwt/qwt_plot_glcanvas.h \
    qwt/qwt_plot_directpainter.h \
    qwt/qwt_plot_dict.h \
    qwt/qwt_plot_curve.h \
    qwt/qwt_plot_canvas.h \
    qwt/qwt_plot_barchart.h \
    qwt/qwt_plot_abstract_barchart.h \
    qwt/qwt_pixel_matrix.h \
    qwt/qwt_picker.h \
    qwt/qwt_picker_machine.h \
    qwt/qwt_panner.h \
    qwt/qwt_painter.h \
    qwt/qwt_painter_command.h \
    qwt/qwt_null_paintdevice.h \
    qwt/qwt_matrix_raster_data.h \
    qwt/qwt_math.h \
    qwt/qwt_magnifier.h \
    qwt/qwt_legend.h \
    qwt/qwt_legend_label.h \
    qwt/qwt_legend_data.h \
    qwt/qwt_knob.h \
    qwt/qwt_interval.h \
    qwt/qwt_interval_symbol.h \
    qwt/qwt_graphic.h \
    qwt/qwt_global.h \
    qwt/qwt_event_pattern.h \
    qwt/qwt_dyngrid_layout.h \
    qwt/qwt_dial.h \
    qwt/qwt_dial_needle.h \
    qwt/qwt_date.h \
    qwt/qwt_date_scale_engine.h \
    qwt/qwt_date_scale_draw.h \
    qwt/qwt_curve_fitter.h \
    qwt/qwt_counter.h \
    qwt/qwt_compat.h \
    qwt/qwt_compass.h \
    qwt/qwt_compass_rose.h \
    qwt/qwt_column_symbol.h \
    qwt/qwt_color_map.h \
    qwt/qwt_clipper.h \
    qwt/qwt_arrow_button.h \
    qwt/qwt_analog_clock.h \
    qwt/qwt_abstract_slider.h \
    qwt/qwt_abstract_scale.h \
    qwt/qwt_abstract_scale_draw.h \
    qwt/qwt_abstract_legend.h \
    snmp_pp/vb.h \
    snmp_pp/v3.h \
    snmp_pp/uxsnmp.h \
    snmp_pp/usm_v3.h \
    snmp_pp/timetick.h \
    snmp_pp/target.h \
    snmp_pp/StdAfx.h \
    snmp_pp/snmpmsg.h \
    snmp_pp/snmperrs.h \
    snmp_pp/snmp_pp.h \
    snmp_pp/smival.h \
    snmp_pp/smi.h \
    snmp_pp/sha.h \
    snmp_pp/reentrant.h \
    snmp_pp/pdu.h \
    snmp_pp/oid.h \
    snmp_pp/oid_def.h \
    snmp_pp/octet.h \
    snmp_pp/notifyqueue.h \
    snmp_pp/msgqueue.h \
    snmp_pp/msec.h \
    snmp_pp/mp_v3.h \
    snmp_pp/md5.h \
    snmp_pp/log.h \
    snmp_pp/IPv6Utility.h \
    snmp_pp/integer.h \
    snmp_pp/idea.h \
    snmp_pp/gauge.h \
    snmp_pp/eventlistholder.h \
    snmp_pp/eventlist.h \
    snmp_pp/ctr64.h \
    snmp_pp/counter.h \
    snmp_pp/config_snmp_pp.h \
    snmp_pp/collect2.h \
    snmp_pp/collect1.h \
    snmp_pp/collect.h \
    snmp_pp/auth_priv.h \
    snmp_pp/asn1.h \
    snmp_pp/address.h

FORMS	= mainw.ui \
        agentprofile.ui \
        usmprofile.ui \
        preferences.ui \
        gotoline.ui \
        find.ui \
        replace.ui \
        varbinds.ui

RESOURCES = snmpb.qrc

LIBS += -lsmi -ltomcrypt

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

win32 {
  CONFIG += release
  QMAKE_CXX = mingw32-g++
  QMAKE_LINK = mingw32-g++
  RC_FILE = snmpb.rc
  QMAKE_RC = windres --preprocessor="$$[QT_INSTALL_PREFIX]\\..\\..\\..\\..\\mingw\\bin\\cpp.exe"
  LIBS	+= -lws2_32 -L../libsmi/win
}
macx:ICON = images/snmpb.icns

