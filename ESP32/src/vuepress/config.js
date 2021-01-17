const { description } = require('../../package')

module.exports = {
  base: '/esp32/',
  /**
   * Ref：https://v1.vuepress.vuejs.org/config/#title
   */
  title: 'ESP32',
  /**
   * Ref：https://v1.vuepress.vuejs.org/config/#description
   */
  description: 'Placa de desarrollo',

  /**
   * Extra tags to be injected to the page HTML `<head>`
   *
   * ref：https://v1.vuepress.vuejs.org/config/#head
   */
  head: [
    ['meta', { name: 'theme-color', content: '#3eaf7c' }],
    ['meta', { name: 'apple-mobile-web-app-capable', content: 'yes' }],
    ['meta', { name: 'apple-mobile-web-app-status-bar-style', content: 'black' }]
  ],

  /**
   * Theme configuration, here is the default theme configuration for VuePress.
   *
   * ref：https://v1.vuepress.vuejs.org/theme/default-theme-config.html
   */
  themeConfig: {
    repo: '',
    editLinks: false,
    docsDir: '',
    editLinkText: '',
    lastUpdated: false,
    nav: [
      {
        text: 'Guia',
        link: '/guia/',
      },
      {
        text: 'Config',
        link: '/config/'
      },
      {
        text: 'YouTube',
        link: 'https://v1.vuepress.vuejs.org'
      }
    ],
      sidebar: 'auto'    
  },

  /**
   * Apply plugins，ref：https://v1.vuepress.vuejs.org/zh/plugin/
   */
  plugins: [
    '@vuepress/plugin-back-to-top',
    '@vuepress/plugin-medium-zoom',
  ],
}
