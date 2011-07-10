<?php
/**
 *  @file
 *  apachesolr_attributes.admin.inc
 *
 *  @author blazey http://drupal.org/user/353861
 */

/**
 *  Settings form.
 */
function apachesolr_attributes_settings_form() {
  // Create options array for all taxonomy_term_refence fields attached to nodes.
  foreach (apachesolr_attributes_get_term_reference_fields() as $field) {
    $fields_options[$field['fieldname']] = t('Field: @label (fieldname: @fieldname, vocabulary: @vocabulary)', array(
        '@label' => $field['label'],
        '@fieldname' => $field['fieldname'],
        '@vocabulary' => $field['vocabulary']->name));
  }

  $form['apachesolr_attributes_fields_enabled'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enable attributes facets for'),
    '#default_value' => variable_get('apachesolr_attributes_fields_enabled', array()),
    '#options' => $fields_options,
    '#description' => t('Facets for all top-level (depth 0) terms of selected vocabularies will be created.'),
  );

  $form['apachesolr_attributes_auto_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto enable facets when new attribute terms are created'),
    '#default_value' => variable_get('apachesolr_attributes_auto_enable', 0),
  );
  
  $form['auto_enable'] = array(
    '#type' => 'fieldset',
    '#title' => t(''),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name=apachesolr_attributes_auto_enable]' => array('checked' => TRUE)
      ),
    ),
  );

  foreach (apachesolr_facetapi_searcher_info() as $searcher => $searcher_info) {
    $searcher_options[$searcher] = $searcher_info['label'];
  }
  $form['auto_enable']['apachesolr_attributes_searcher'] = array(
    '#type' => 'select',
    '#title' => t('Searcher'),
    '#default_value' => variable_get('apachesolr_attributes_searcher', 0),
    '#options' => $searcher_options,
  );

  foreach (facetapi_get_realm_info() as $realm) {
    $realm_options[$realm['name']] = $realm['label'];
  }
  $form['auto_enable']['apachesolr_attributes_realm'] = array(
    '#type' => 'select',
    '#title' => t('Realm'),
    '#default_value' => variable_get('apachesolr_attributes_realm', 'block'),
    '#options' => $realm_options,
    '#description' => t('Realm for auto enabled facets'),
  );

  $form['auto_enable']['apachesolr_attributes_block_region'] = array(
    '#type' => 'select',
    '#title' => t('Region'),
    '#default_value' => variable_get('apachesolr_attributes_block_region', 'sidebar-first'),
    '#options' => system_region_list(variable_get('theme_default', 'bartik')),
    '#description' => t('Region to put enabled blocks into'),
  );

  return system_settings_form($form);
}