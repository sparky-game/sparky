import { themes as prismThemes } from 'prism-react-renderer';

const config = {
  title: 'Sparky - 5v5 character-based libre tactical shooter',
  tagline: 'A 5v5, blazingly flast, character-based libre tactical shooter written in pure C.',
  favicon: 'img/favicon.png',
  url: 'https://iwas-coder.github.io',
  baseUrl: '/sparky',
  organizationName: 'iWas-Coder',
  projectName: 'sparky',
  trailingSlash: false,
  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',

  i18n: {
    defaultLocale: 'en',
    locales: ['en']
  },

  presets: [
    [
      'classic',
      {
        docs: {
          sidebarPath: './sidebars.js',
          editUrl: 'https://github.com/iWas-Coder/sparky/blob/master/docs/www/docs/',
          showLastUpdateTime: true
        },
        blog: {
          showReadingTime: true,
          editUrl: 'https://github.com/iWas-Coder/sparky/blob/master/docs/www/blog/'
        },
        theme: {
          customCss: './src/css/custom.css'
        }
      }
    ]
  ],

  themeConfig: ({
    navbar: {
      logo: {
        alt: 'Sparky Logo',
        src: 'img/favicon.png'
      },
      items: [
        {
          href: 'https://github.com/iWas-Coder/sparky',
          className: 'header-github-link',
          'aria-label': 'GitHub',
          position: 'right'
        },
        {
          href: 'https://iwas-coder.itch.io/sparky',
          className: 'header-itchio-link',
          'aria-label': 'itch.io',
          position: 'right'
        },
        {
          href: 'https://buymeacoffee.com/iwas.coder',
          className: 'header-bmac-link',
          'aria-label': 'Buy Me A Coffee',
          position: 'right'
        },
        {
          type: 'docSidebar',
          sidebarId: 'docs',
          position: 'left',
          label: 'Docs'
        },
        {
          to: 'blog',
          position: 'left',
          label: 'Blog'
        }
      ],
    },
    algolia: {
      appId: 'NQFRICJH33',
      apiKey: 'b7e7597d510e0f0a58977359d95f64ca',
      indexName: 'iwas-coderio',
      contextualSearch: true
    },
    footer: {
      style: 'dark',
      links: [
        {
          title: 'Docs',
          items: [
            {
              label: 'What is Sparky?',
              to: 'docs/overview/1.1-what-is-sparky'
            },
            {
              label: 'Getting started',
              to: 'docs/getting-started/2.1-getting-started'
            }
          ]
        },
        {
          title: 'Community',
          items: [
            {
              label: 'Contributing',
              href: 'https://github.com/iWas-Coder/sparky/blob/master/CONTRIBUTING.org'
            },
            {
              label: 'Code of Conduct',
              href: 'https://github.com/iWas-Coder/sparky/blob/master/CODE_OF_CONDUCT.md'
            }
          ]
        },
        {
          title: 'More',
          items: [
            {
              label: 'GitHub',
              href: 'https://github.com/iWas-Coder/sparky'
            },
            {
              label: 'itch.io',
              href: 'https://iwas-coder.itch.io/sparky'
            },
            {
              label: 'Buy Me a Coffee',
              href: 'https://buymeacoffee.com/iwas.coder'
            }
          ]
        }
      ],
      copyright: `Copyright © ${new Date().getFullYear()} Wasym Atieh Alonso. All rights reserved.`,
    },
    prism: {
      theme: prismThemes.github,
      darkTheme: prismThemes.dracula,
    }
  })
};

export default config;
